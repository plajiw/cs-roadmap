#!/bin/bash

# Script para buscar temas em arquivos .md
# Uso: ./search-md.sh "docker compose"
# ou:  ./search-md.sh (vai pedir o tema interativamente)

SEARCH_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
THEME="$1"

# Se não recebeu argumento, pede interativamente
if [ -z "$THEME" ]; then
  read -p "Digite o tema a buscar: " THEME
fi

if [ -z "$THEME" ]; then
  echo "Erro: Tema não fornecido!"
  exit 1
fi

echo "🔍 Buscando por: '$THEME'"
echo "📁 Diretório: $SEARCH_DIR"
echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"

# Busca case-insensitive
grep -r -i -l "$THEME" "$SEARCH_DIR" --include="*.md" | while read -r file; do
  # Caminho relativo
  rel_path="${file#$SEARCH_DIR/}"

  # Conta ocorrências
  count=$(grep -i -o "$THEME" "$file" | wc -l)

  # Extrai primeira linha com match (contexto)
  context=$(grep -i -m 1 "$THEME" "$file" | sed 's/^[[:space:]]*//;s/[[:space:]]*$//')

  echo ""
  echo "📄 $rel_path"
  echo "   Ocorrências: $count"
  echo "   Preview: ${context:0:80}..."
done

echo ""
echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
echo "✅ Busca concluída!"
