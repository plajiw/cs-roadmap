# Critérios de Melhoria de Anotações

Documento que padroniza os critérios e técnicas aplicadas ao melhorar e reorganizar anotações técnicas. Baseado na reorganização bem-sucedida das anotações sobre Docker (2025-04-14).

## Princípios Gerais

1. **Preservação total do conteúdo original** — Nenhuma informação é removida, apenas reorganizada e melhorada.
2. **Hierarquia clara** — Estrutura lógica de seções principais, subsecções e subseções.
3. **Linguagem direta e técnica** — PT-BR, sem metáforas ou exemplos lúdicos, focado em conceitos práticos.
4. **Exemplos acadêmicos/realistas** — Exemplos curtos, focados no conceito, aplicáveis em cenários reais.

## Estrutura Recomendada

### Nível 1: Título Principal
```markdown
# Tema Principal
```

Introdução contextual (1-2 parágrafos máximo) explicando o escopo do documento.

### Nível 2: Seções temáticas
```markdown
## Seção (Conceitual ou Procedimental)
```

Cada seção agrupa um tema coeso. Evitar mais de 8-10 seções por documento.

### Nível 3: Subsecções
```markdown
### Subsecção
```

Quebrar seções grandes em subsecções quando houver múltiplos subtópicos. Máximo 5-7 subsecções por seção.

**Padrão comum para seções procedimentais:**

1. **Motivação / Contexto** — Por que essa seção é importante?
2. **Conceito** — Definição ou explicação teórica breve.
3. **Sintaxe / Estrutura** — Como usar, fórmula, estrutura do comando.
4. **Exemplo prático** — Código ou passo a passo.
5. **Tabela comparativa/explicativa** — Quando apropriado.

## Técnicas de Formatação

### Tabelas para Comparação e Referência Rápida

**Quando usar:**
- Listar alternativas (VMs vs Containers vs Servidores)
- Enumerar opções de comando com descrições
- Comparar características de componentes
- Explicar campos ou parâmetros de saída

**Exemplo padrão:**

```markdown
| Elemento | Descrição |
|----------|-----------|
| Item 1 | Explicação breve |
| Item 2 | Explicação breve |
```

### Blocos de Código Estruturados

**Quando usar:**
- Comandos shell/terminal
- Dockerfiles e configurações
- JSON, YAML ou estruturas estruturadas
- Exemplos de saída esperada

**Padrão:**

```markdown
Explicação antes do bloco:

\`\`\`bash
# Comando com comentário
comando --opção valor
\`\`\`

Explicação após o bloco (se necessário).
```

### Listas com Negritos para Campos

**Para explanar parâmetros ou conceitos:**

```markdown
- `-opção` (--nome-longo): Descrição do que faz.
- `-outro` (--outro-nome): Outra descrição.
```

**Para componentes com roles:**

- **Nome do Componente:** Responsabilidade e função.

### Blocos Informativos com Contexto Windows

Para sistemas diferentes ou considerações específicas de plataforma:

```markdown
### Considerações em Windows (Git Bash / MINGW64)

No Windows com Git Bash, pode ser necessário...
```

## Padrões de Conteúdo

### Seção de Conceitos Fundamentais

Explica os blocos de construção antes de uso prático.

**Estrutura:**

```markdown
## Conceitos Fundamentais

Breve introdução.

| Conceito | Analogia | Descrição |
|----------|----------|-----------|
| Item A | Paralelo | O que é e por que importa |
| Item B | Paralelo | O que é e por que importa |

Detalhes adicionais em parágrafos ou subsecções se necessário.
```

### Seção Procedimental (Como Fazer)

Segue padrão: Motivação → Conceito → Sintaxe → Exemplo → Validação/Inspeção.

**Exemplo:**

```markdown
## Mapeamento de Diretórios (Volumes)

### Motivação
Por que você precisa disso?

### Conceito
O que é e como funciona?

### Sintaxe
Comando ou estrutura.

### Exemplo Prático
Passos concretos ou código.

### Validação/Verificação
Como confirmar que funcionou?
```

### Seção de Referência Rápida

Resumo denso de comandos ou opções para consulta rápida.

**Estrutura:**

```markdown
## Referência Rápida de Help

\`\`\`bash
comando --help
\`\`\`

Ou tabela com comandos principais.
```

## Correções de Linguagem

### Acentuação e Ortografia

- Corrigir para padrão PT-BR moderno.
- Exemplos frequentes em anotações rápidas:
  - "e" → "é" (verbo ser)
  - "nao" → "não"
  - "conteiner" → "container" (termo técnico internacional)
  - "dockertfile" → "Dockerfile" (nome próprio)
  - "maquina virtual" → "máquina virtual"
  - "diretorio" → "diretório"

### Estrutura de Frases

- Remover listas sem estrutura (colchetes soltos, fragmentos).
- Transformar fragmentos em frases completas ou listas bem formatadas.
- Exemplo de antes/depois:

**Antes:**
```
Problemas da virtualização
- nbecessidade de baixar o sistema de operacional em cada máquina virtual
Cuistos de manutenção
```

**Depois:**
```markdown
## Problemas da virtualização

- Necessidade de baixar o sistema operacional em cada máquina virtual.
- Custos de manutenção e configuração.
```

### Remoção de Artefatos

- Remover prompts de terminal desnecessários (pode ser útil manter um para contexto).
- Remover textos incompletos ou cortados.
- Limpar output visualmente poluído mantendo informação essencial.

## Organização Lógica

### Agregar conteúdo relacionado

**Antes:** Informação espalhada em vários parágrafos soltos.

**Depois:** Grupos temáticos em subsecções com cabeçalhos.

### Separar teoria de prática

Se uma seção mistura fundamentação teórica com procedimentos:

1. **Subsecção 1: Teoria/Conceitos** → Explicações sem comandos.
2. **Subsecção 2: Sintaxe** → Estrutura esperada.
3. **Subsecção 3: Exemplo Prático** → Código executável.

### Evitar duplicação

Se duas seções tratam do mesmo assunto:
- Mover um para referência da outra.
- Consolidar em uma única seção com subsecções temáticas.

## Checklist de Revisão

Ao melhorar uma anotação, verificar:

- [ ] Todas as informações originais foram preservadas?
- [ ] Existe hierarquia clara (# → ## → ###)?
- [ ] Seções estão em ordem lógica (fundação antes de prática)?
- [ ] Tabelas foram usadas para listas comparativas?
- [ ] Exemplos práticos são curtos e diretos?
- [ ] Acentuação está conforme PT-BR moderno?
- [ ] Não há artefatos de terminal ou texto incompleto?
- [ ] Parágrafos têm máximo 3-4 frases?
- [ ] Negritos destacam componentes-chave?
- [ ] Há subsecções quando seções ultrapassam 500 palavras?

## Exemplo Aplicado: Seção sobre Containers

**Antes (desorganizado):**
```
no linux é ncessario passar o sudo sempre
sudo groupadd docker
...
[comandos misturados com explicações]
...
docker container run -it alpine /bin/sh
-i intereative -t terminal ou -it
um contaier nn tem como integragir com outros container
```

**Depois (reorganizado):**
```markdown
## Configuração inicial no Linux

No Linux é necessário configurar permissões para usar Docker sem `sudo` em cada comando:

\`\`\`bash
sudo groupadd docker
sudo gpasswd -a <user> docker
sudo service docker restart
newgrp docker
\`\`\`

## Modo interativo

\`\`\`bash
docker container run -it alpine /bin/sh
\`\`\`

Opções:
- `-i` (--interactive): Mantém stdin aberto mesmo desconectado
- `-t` (--tty): Aloca pseudo-terminal
- `-it`: Combinação para shell interativo

## Isolamento entre containers

Um container não tem como interagir com outro container...
```

## Aplicação Prática

Esta metodologia foi aplicada em:
- **01-docker-introduction.md** — Correção de acentuação + estruturação
- **02-docker-overview.md** — Reorganização lógica + tabelas comparativas
- **03-docker-architeure.md** — Reestruturação + fluxograma textual
- **04-docker-container-operations.md** — Procedimentos com padrão Motivação→Sintaxe→Exemplo

Resultado: Anotações claras, navegáveis e reutilizáveis.
