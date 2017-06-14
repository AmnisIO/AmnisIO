import { Node, SyntaxKind, SourceFile } from 'typescript';
import { emitImportDeclaration } from './imports';
import { emitFunctionLikeDeclaration } from './functions';
import { emitExpressionStatement, emitCallExpressionStatement, emitConditionalExpression, emitBinaryExpression } from './expressions';
import { emitColonToken, emitQuestionToken, emitEqualsEqualsToken } from './tokens';
import { emitIdentifier, emitType } from './identifiers';
import { emitBlock } from './blocks';
import { emitSourceFile } from './source';
import { emitReturnStatement } from './statements';
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
    case SyntaxKind.SourceFile: return emitSourceFile(<any>node, context);
    case SyntaxKind.ImportDeclaration: return emitImportDeclaration(<any>node, context);
    case SyntaxKind.FunctionDeclaration: return emitFunctionLikeDeclaration(<any>node, context);
    case SyntaxKind.ExpressionStatement: return emitExpressionStatement(<any>node, context);
    case SyntaxKind.CallExpression: return emitCallExpressionStatement(<any>node, context);
    case SyntaxKind.ConditionalExpression: return emitConditionalExpression(<any>node, context);
    case SyntaxKind.Identifier: return emitIdentifier(<any>node, context);
    case SyntaxKind.TypeReference: return emitType(<any>node, context);
    case SyntaxKind.Block: return emitBlock(<any>node, context);
    case SyntaxKind.ReturnStatement: return emitReturnStatement(<any>node, context);
    case SyntaxKind.EqualsEqualsEqualsToken:
    case SyntaxKind.EqualsEqualsToken: return emitEqualsEqualsToken(node, context);
    case SyntaxKind.QuestionToken: return emitQuestionToken(<any>node, context);
    case SyntaxKind.ColonToken: return emitColonToken(<any>node, context);
    case SyntaxKind.EndOfFileToken: return { context, emitted_string: '\n' };
    case SyntaxKind.VariableStatement: return ignore(node, context);
    case SyntaxKind.BinaryExpression: return emitBinaryExpression(<any>node, context);
    default: return ignore(node, context);
  }
};
