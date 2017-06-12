import { Node, SyntaxKind, SourceFile } from 'typescript';
import { emitImportDeclaration } from './imports';
import { emitFunctionLikeDeclaration } from './functions';
import { emitExpressionStatement } from './expressions';

export const emit = (node: Node): string => {
  switch (node.kind) {
    case SyntaxKind.SourceFile: return (<SourceFile>node).statements.map(node => emit(node)).join('\n');
    case SyntaxKind.ImportDeclaration: return emitImportDeclaration(<any>node);
    case SyntaxKind.FunctionDeclaration: return emitFunctionLikeDeclaration(<any>node);
    case SyntaxKind.ExpressionStatement: return emitExpressionStatement(<any>node);
    case SyntaxKind.EndOfFileToken: return 'end';
    default: throw new Error(`unknown syntax kind ${SyntaxKind[node.kind]}`);
  }
};
