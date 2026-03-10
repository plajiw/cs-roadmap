# 06-system-design-case-studies

Esta trilha e uma area especial do roadmap. Ela nao existe para aprender fundamentos do zero, mas para consolidar conhecimentos vindos das trilhas anteriores em exercicios de system design, analise arquitetural e documentacao de decisoes tecnicas.

Aqui o foco sai do estudo isolado de tecnologia e entra na aplicacao real de conceitos: requisitos, escala, disponibilidade, consistencia, custos, trade-offs e clareza de comunicacao tecnica.

## Papel desta trilha no roadmap

- `01-computer-science` fornece base de algoritmos, estruturas de dados e raciocinio.
- `02-dotnet-mastery` fornece profundidade de stack e runtime.
- `03-architecture-design` fornece padroes, principios e estrutura.
- `04-distributed-systems` fornece o modelo mental de escala, comunicacao e falhas.
- `05-platform-reliability` cobre entrega, operacao e confiabilidade em producao.
- `06-system-design-case-studies` junta tudo isso em cenarios realistas e discutiveis.

## Estrutura recomendada

| Pasta | Foco principal | Exemplos de estudo |
| --- | --- | --- |
| `system-design-scenarios` | Estudos de desenho de sistemas ponta a ponta | URL shortener, chat system, ride-sharing, streaming platform, notification system |
| `decision-records-and-trade-offs` | Registro de decisoes tecnicas e comparacao de alternativas | ADRs, escolhas de banco, consistency models, cache strategy, sync vs async communication |

## Regras de separacao

- Se o objetivo e desenhar um sistema, estimar carga, decompor componentes e discutir arquitetura alvo, o conteudo pertence a `system-design-scenarios`.
- Se o objetivo e registrar uma escolha tecnica, justificar alternativas ou documentar consequencias arquiteturais, o conteudo pertence a `decision-records-and-trade-offs`.

## Como estudar aqui

1. Escolha um problema realista.
2. Defina requisitos funcionais e nao funcionais.
3. Proponha uma arquitetura inicial.
4. Identifique gargalos, riscos e trade-offs.
5. Registre a evolucao do raciocinio de forma clara.

## Estrutura interna de cada modulo

Cada pasta segue o mesmo formato padrao do projeto:

- `summary.md`: escopo curto do modulo.
- `links.md`: referencias, entrevistas, talks e materiais de apoio.
- `notes/`: raciocinio, requisitos, estimativas e anotacoes.
- `src/`: diagramas, simulacoes, pequenos artefatos ou POCs quando fizer sentido.
- `articles/`: rascunhos de write-ups tecnicos e estudos publicados.

O objetivo desta trilha nao e acumular muitos casos rapidamente. O objetivo e produzir poucos estudos, mas com profundidade, clareza e justificativa tecnica forte.