#ifndef TAC_H
#define TAC_H

#include "../ast/ast.h"

/*
 * Generates Three Address Code for the given (semantically valid)
 * AST and prints it to stdout, one instruction per line.
 *
 * Should only be called after analyze_semantics() has returned 0
 * errors -- codegen assumes the tree is well-typed.
 */
void generate_tac(ASTNode *root);

#endif