#ifndef SEMANTIC_H
#define SEMANTIC_H

#include "../ast/ast.h"

/*
 * Walks the AST, builds the symbol table as it goes, and checks:
 *   - redeclaration of a variable within the same scope
 *   - use of an undeclared variable
 *   - type mismatches in assignments
 *   - type errors in arithmetic / relational / logical expressions
 *   - non-boolean condition in if / while
 *
 * As a side effect, every expression node's `data_type` field is
 * filled in with its inferred type, ready for use by codegen.
 *
 * Returns the number of semantic errors found (0 = success).
 */
int analyze_semantics(ASTNode *root);

#endif