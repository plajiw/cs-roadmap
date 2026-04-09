#!/usr/bin/env bash
set -euo pipefail

# Uso: ./new-roadmap-topic.sh <trilha> <tema>
# Exemplo: ./new-roadmap-topic.sh 01-computer-science-foundations graph-theory

track="${1:-}"
topic="${2:-}"

if [[ -z "$track" || -z "$topic" ]]; then
  echo "Uso: $0 <trilha> <tema>"
  exit 1
fi

base="roadmap/$track/$topic"
mkdir -p "$base"/{notes,articles,study,src/{playground,problems}}

# Arquivos criados em branco, sem conteudo inicial.
touch \
  "$base/summary.md" \
  "$base/study/01-context.md" \
  "$base/study/02-references.md" \
  "$base/study/03-courses.md" \
  "$base/study/04-books.md" \
  "$base/study/05-practice.md" \
  "$base/notes/note.md" \
  "$base/articles/article.md"

# Pastas que iniciam vazias recebem .gitkeep.
touch \
  "$base/src/playground/.gitkeep" \
  "$base/src/problems/.gitkeep"

echo "Tema criado em: $base"
