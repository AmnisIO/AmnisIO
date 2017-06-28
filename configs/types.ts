export interface Library {
  repository: string;
  paths: string[];
}

export interface BoardConfiguration {
  board: string;
  dependencies: string[];
  libraries: Library[];
}
