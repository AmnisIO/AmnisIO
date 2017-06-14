import { Node, SyntaxKind, SourceFile, TypeReferenceNode, Identifier, Block, ExpressionStatement } from 'typescript';
import { emitImportDeclaration } from './imports';
import { emitFunctionLikeDeclaration, emitVariableDeclaration } from './declarations';
import { emitCallExpression, emitConditionalExpression, emitBinaryExpression } from './expressions';
import { emitColonToken, emitQuestionToken, emitEqualsEqualsToken } from './tokens';
import { emitIdentifier, emitType } from './identifiers';
import { emitBlock } from './blocks';
import { emitSourceFile } from './source';
import { emitReturnStatement, emitVariableStatement, emitExpressionStatement } from './statements';
import { Context } from '../contexts';

export interface EmitResult {
  context: Context;
  emitted_string: string;
}

const ignore = (node: Node, context: Context): EmitResult => ({
  context,
  emitted_string: `ignored_${SyntaxKind[node.kind]}`
})

export const emitString = (node: Node, context: Context): string => emit(node, context).emitted_string;

export const emit = (node: Node, context: Context): EmitResult => {
  switch (node.kind) {
    // Source
    case SyntaxKind.SourceFile:
      return emitSourceFile(<SourceFile>node, context);

    // Identifiers
    case SyntaxKind.Identifier:
      return emitIdentifier(<Identifier>node, context);

    // Names

    // Signature Elements

    // Type Members

    // Types
    case SyntaxKind.TypeReference:
      return emitType(<TypeReferenceNode>node, context);

    // Statements
    case SyntaxKind.Block:
      return emitBlock(<Block>node, context);
    case SyntaxKind.ExpressionStatement:
      return emitExpressionStatement(<ExpressionStatement>node, context);
    case SyntaxKind.ReturnStatement:
      return emitReturnStatement(<any>node, context);
    case SyntaxKind.VariableStatement:
      return emitVariableStatement(<any>node, context);

    // Declarations
    case SyntaxKind.ImportDeclaration:
      return emitImportDeclaration(<any>node, context);
    case SyntaxKind.FunctionDeclaration:
      return emitFunctionLikeDeclaration(<any>node, context);
    case SyntaxKind.VariableDeclaration:
      return emitVariableDeclaration(<any>node, context);

    // Expressions
    case SyntaxKind.CallExpression:
      return emitCallExpression(<any>node, context);
    case SyntaxKind.ConditionalExpression:
      return emitConditionalExpression(<any>node, context);
    case SyntaxKind.BinaryExpression:
      return emitBinaryExpression(<any>node, context);

    // Clauses

    // Property Assignments

    // Tokens
    case SyntaxKind.EqualsEqualsEqualsToken:
    case SyntaxKind.EqualsEqualsToken:
      return emitEqualsEqualsToken(node, context);
    case SyntaxKind.QuestionToken:
      return emitQuestionToken(<any>node, context);
    case SyntaxKind.ColonToken:
      return emitColonToken(<any>node, context);
    case SyntaxKind.EndOfFileToken:
      return { context, emitted_string: '\n' };

    // Ignore others
    default:
      return ignore(node, context);
  }
};
