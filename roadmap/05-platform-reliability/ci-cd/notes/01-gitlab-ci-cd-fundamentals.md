# 01 - GitLab CI/CD Fundamentals

## O que é **CI/CD**

 **Integração Contínua** e **Entrega ou Implantação Contínua**, é um conjunto de práticas de automatiza e acelera o ciclo de vida do desenvolvimento de software, desde a escrita até a implementação em produção.

### Integração Contínua

É a prática de integrar, de forma automática e frequente mudanças em um repositório de código-fonte compartilhado. Após cada integração, são executados testes automatizados (unitários, de integração, estáticos) para detectar erros rapidamente, garantindo que o código permaneça estável e de qualidade. A CI garante que que as mudanças de código de diferentes membros da equipe não introduzam conflitos e que a qualidade seja mantida, permitindo que os desenvolvedores trabalhem simultaneamente sem interromper a estabilidade da base de código.

### Entrega Contínua

É um processo em 

### Implantação Contínua

## Definição de Pipeline

Um pipeline é uma sequência de etapas interligadas que processa dados, tarefas ou fluxos de trabalho de forma automatizada e ordenada, funcionando como uma "tubulação" que conecta diferentes estágios para alcançar um objetivo final.

## Pipeline e CI/CD no GitLab

- Arquivo `.gitlab-ci.xml` é um YMAL customizado na raiz do projeto que especifica os estágios (stages), operações (jobs) e scripts que serão executados durante o CI/CD.

- Os estágios (Stages) determinam a ordem de execução. Podem ser `build`, `test` ou `deploy`.

- as operações (jobs) especifica as tarefas que vão ocorrer em casa estágio. Por exemplo, compilar ou testar código.
