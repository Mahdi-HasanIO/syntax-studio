#include "tac.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

typedef struct
{
    char **lines;
    int count;
    int capacity;
} TACList;

static TACList tac_list = {NULL, 0, 0};
static int temp_count = 0;
static int label_count = 0;

static void tac_emit(const char *fmt, ...)
{
    char buffer[256];
    va_list args;

    va_start(args, fmt);
    vsnprintf(buffer, sizeof(buffer), fmt, args);
    va_end(args);

    if (tac_list.count == tac_list.capacity)
    {
        tac_list.capacity = tac_list.capacity == 0 ? 32 : tac_list.capacity * 2;
        tac_list.lines = (char **)realloc(tac_list.lines,
                                           tac_list.capacity * sizeof(char *));

        if (tac_list.lines == NULL)
        {
            fprintf(stderr, "Memory allocation failed.\n");
            exit(EXIT_FAILURE);
        }
    }

    tac_list.lines[tac_list.count++] = strdup(buffer);
}

static char *new_temp(void)
{
    char buffer[16];
    snprintf(buffer, sizeof(buffer), "t%d", temp_count++);
    return strdup(buffer);
}

static char *new_label(void)
{
    char buffer[16];
    snprintf(buffer, sizeof(buffer), "L%d", label_count++);
    return strdup(buffer);
}

static void gen_stmt(ASTNode *stmt);
static void gen_stmt_list(ASTNode *list);

/*
 * Generates code for an expression and returns the name of the
 * place (variable, literal, or temp) holding its value. Caller
 * owns the returned string and must free() it.
 */
static char *gen_expr(ASTNode *expr)
{
    if (expr == NULL)
        return strdup("?");

    switch (expr->type)
    {
        case NODE_IDENTIFIER:
        case NODE_INT_LITERAL:
        case NODE_FLOAT_LITERAL:
        case NODE_BOOL_LITERAL:
            return strdup(expr->text);

        case NODE_UNARY_OP:
        {
            char *operand = gen_expr(expr->left);
            char *temp = new_temp();

            tac_emit("%s = %s%s", temp, expr->text, operand);

            free(operand);
            return temp;
        }

        case NODE_BINARY_OP:
        {
            char *l = gen_expr(expr->left);
            char *r = gen_expr(expr->right);
            char *temp = new_temp();

            tac_emit("%s = %s %s %s", temp, l, expr->text, r);

            free(l);
            free(r);
            return temp;
        }

        default:
            return strdup("?");
    }
}

static void gen_stmt(ASTNode *stmt)
{
    if (stmt == NULL)
        return;

    switch (stmt->type)
    {
        case NODE_DECLARATION:
            /* No runtime instruction needed; kept as a comment for readability. */
            tac_emit("// declare %s : %s", stmt->text, stmt->data_type);
            break;

        case NODE_ASSIGNMENT:
        {
            char *rhs = gen_expr(stmt->left);
            tac_emit("%s = %s", stmt->text, rhs);
            free(rhs);
            break;
        }

        case NODE_PRINT:
        {
            char *val = gen_expr(stmt->left);
            tac_emit("print %s", val);
            free(val);
            break;
        }

        case NODE_IF:
        {
            char *cond = gen_expr(stmt->left);

            if (stmt->third == NULL)
            {
                char *Lend = new_label();

                tac_emit("ifFalse %s goto %s", cond, Lend);
                gen_stmt(stmt->right); /* then-block */
                tac_emit("%s:", Lend);

                free(Lend);
            }
            else
            {
                char *Lelse = new_label();
                char *Lend = new_label();

                tac_emit("ifFalse %s goto %s", cond, Lelse);
                gen_stmt(stmt->right); /* then-block */
                tac_emit("goto %s", Lend);
                tac_emit("%s:", Lelse);
                gen_stmt(stmt->third); /* else-block */
                tac_emit("%s:", Lend);

                free(Lelse);
                free(Lend);
            }

            free(cond);
            break;
        }

        case NODE_WHILE:
        {
            char *Lstart = new_label();
            char *Lend = new_label();

            tac_emit("%s:", Lstart);

            char *cond = gen_expr(stmt->left);
            tac_emit("ifFalse %s goto %s", cond, Lend);
            free(cond);

            gen_stmt(stmt->right); /* body block */

            tac_emit("goto %s", Lstart);
            tac_emit("%s:", Lend);

            free(Lstart);
            free(Lend);
            break;
        }

        case NODE_BLOCK:
            gen_stmt_list(stmt->left);
            break;

        default:
            break;
    }
}

static void gen_stmt_list(ASTNode *list)
{
    for (ASTNode *s = list; s != NULL; s = s->next)
        gen_stmt(s);
}

void generate_tac(ASTNode *root)
{
    temp_count = 0;
    label_count = 0;
    tac_list.count = 0;

    if (root != NULL && root->type == NODE_PROGRAM)
        gen_stmt_list(root->left);

    for (int i = 0; i < tac_list.count; i++)
    {
        /* Labels get printed flush-left, everything else indented. */
        if (strchr(tac_list.lines[i], ':') != NULL &&
            strncmp(tac_list.lines[i], "//", 2) != 0)
            printf("%s\n", tac_list.lines[i]);
        else
            printf("    %s\n", tac_list.lines[i]);

        free(tac_list.lines[i]);
    }

    free(tac_list.lines);
    tac_list.lines = NULL;
    tac_list.capacity = 0;
}