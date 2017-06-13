import { Node, SyntaxKind, SourceFile } from 'typescript';
import { emitImportDeclaration } from './imports';
import { emitFunctionLikeDeclaration } from './functions';
import { emitExpressionStatement, emitCallExpressionStatement } from './expressions';
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
  emitted_string: `ignored ${SyntaxKind[node.kind]}`
})

export const emit = (node: Node, context: Context): EmitResult => {
  switch (node.kind) {
    case SyntaxKind.SourceFile: return emitSourceFile(<any>node, context);
    case SyntaxKind.ImportDeclaration: return emitImportDeclaration(<any>node, context);
    case SyntaxKind.FunctionDeclaration: return emitFunctionLikeDeclaration(<any>node, context);
    case SyntaxKind.ExpressionStatement: return emitExpressionStatement(<any>node, context);
    case SyntaxKind.CallExpression: return emitCallExpressionStatement(<any>node, context);
    case SyntaxKind.Identifier: return emitIdentifier(<any>node, context);
    case SyntaxKind.TypeReference: return emitType(<any>node, context);
    case SyntaxKind.Block: return emitBlock(<any>node, context);
    case SyntaxKind.ReturnStatement: return emitReturnStatement(<any>node, context);
    case SyntaxKind.EndOfFileToken: return { context, emitted_string: 'end' };
    case SyntaxKind.ConditionalExpression: return ignore(node, context);
    case SyntaxKind.VariableStatement: return ignore(node, context);
    case SyntaxKind.BinaryExpression: return ignore(node, context);  
    default: throw new Error(`unknown syntax kind ${SyntaxKind[node.kind]}`);
  }
};
