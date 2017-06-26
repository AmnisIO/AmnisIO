export interface BoardConfiguration {
  platformio_identifier: string;
  library_repositories: string[];
  library_file_globs: string[];
  exclude_library_file_globs: string[];
}
