import { Node, SyntaxKind, SourceFile } from 'typescript';
import { emitImportDeclaration } from './imports';
import { emitFunctionLikeDeclaration } from './functions';
import { emitExpressionStatement } from './expressions';
import { emitIdentifier, emitType } from './identifiers';
import { emitSourceFile } from './source';
import { Context } from '../contexts';

export interface EmitResult {
  context: Context;
  emitted_string: string;
}

export const emit = (node: Node, context: Context): EmitResult => {
  switch (node.kind) {
    case SyntaxKind.SourceFile: return emitSourceFile(<any>node, context);
    case SyntaxKind.ImportDeclaration: return emitImportDeclaration(<any>node, context);
    case SyntaxKind.FunctionDeclaration: return emitFunctionLikeDeclaration(<any>node, context);
    case SyntaxKind.ExpressionStatement: return emitExpressionStatement(<any>node, context);
    case SyntaxKind.Identifier: return emitIdentifier(<any>node, context);
    case SyntaxKind.TypeReference: return emitType(<any>node, context);
    case SyntaxKind.EndOfFileToken: return { context, emitted_string: 'end' };
    default: throw new Error(`unknown syntax kind ${SyntaxKind[node.kind]}`);
  }
};
