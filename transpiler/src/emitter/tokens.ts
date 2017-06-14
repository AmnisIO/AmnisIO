import { QuestionToken, ColonToken, Token, SyntaxKind, Node } from 'typescript';
import { Context } from '../contexts';
import { EmitResult, emit, emitString } from './';

export const emitQuestionToken = (node: QuestionToken, context: Context): EmitResult => ({
  context,
  emitted_string: '?'
});

export const emitColonToken = (node: ColonToken, context: Context): EmitResult => ({
  context,
  emitted_string: ':'
});

export const emitEqualsEqualsToken = (node: Node, context: Context): EmitResult => ({
  context,
  emitted_string: '=='
});

export const emitFirstAssignmentToken = (node: Node, context: Context): EmitResult => ({
  context,
  emitted_string: '='
});
