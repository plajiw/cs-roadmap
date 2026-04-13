
# Visão geral do Docker

Docker surgiu como solução para os problemas de infraestrutura em evolução ao longo dos anos. Para entender seu papel, é útil compreender como a computação corporativa evoluiu de modelos tradicionais até a containerização.

## Evolução da infraestrutura

### Servidores dedicados (passado)

No passado era comum haver diversos servidores locais para executar diferentes funções (Apache, Microsoft IIS, bancos de dados, etc.).

**Problemas:**
- Alto custo de manutenção de hardware, software e rede.
- Grande ociosidade operacional; difícil otimizar recursos máximos quando máquinas tinham picos curtos de uso e longos períodos ociosos.
- Baixa escalabilidade.
- Difícil manutenção de múltiplas máquinas heterogêneas.

### Máquinas virtuais (intermediária)

A virtualização surgiu através do Hypervisor, que trabalha acima do sistema operacional emulando hardware dentro da máquina virtual. Isso permitiu:

- Criar diversas máquinas virtuais em um único host físico.
- Melhor aproveitamento de recursos e redução de ociosidade.
- Menor custo de hardware.
- Melhor gerenciamento de software.

**Problemas da virtualização:**
- Necessidade de baixar o sistema operacional completo em cada máquina virtual (que pode ser diferente).
- Custos de manutenção e configuração de cada SO.
- Distribuição de atualizações é complexa e demorada.

### Containers (atual)

Para contornar esses problemas surgiu a tecnologia de container: capacidade de empacotar uma aplicação com todas as suas dependências em uma unidade padronizada para desenvolvimento de software, sem necessidade de máquina virtual ou sistema operacional completo.

Nos containers:
- Saturam diretamente no sistema operacional, compartilhando os recursos do kernel com o host.
- Dividem o mesmo SO.
- Compartilham recursos do kernel (I/O, memória, rede, etc.).

## Por que containers são necessários

Mesmo em uma única máquina, surgem problemas de gerenciamento quando múltiplas aplicações competem por recursos:

| Problema                        | Impacto                                         |
|---------------------------------|-------------------------------------------------|
| Conflito de portas de rede      | Duas aplicações não podem usar a mesma porta    |
| Versões diferentes de linguagem | Uma app precisa Python 3.9, outra precisa 3.12  |
| Dependências conflitantes       | Bibliotecas incompatíveis causam falhas         |
| Isolamento insuficiente         | Falha em uma app afeta outras no mesmo servidor |

Containers resolvem esses problemas fornecendo isolamento de processo, rede e sistema de arquivos.

## O que é um container no Docker

Um container é um espaço reservado que é **independente e isolado** de outros containers ou do próprio host. Ele é uma tecnologia de virtualização de ambientes semelhante a máquinas virtuais, mas com uma diferença crucial:

**Diferença fundamental:** No Docker, o kernel é compartilhado com o sistema operacional do host, ao contrário das VMs que virtualizam todo o hardware.

**Efeitos práticos:**
- Desempenho aumenta significativamente.
- Consumo de memória diminui em relação às VMs.
- Menor consumo de espaço em disco.
- Overhead mínimo possível.

Para execução em um container, está associado a ele:
- Um sistema de arquivos completo e isolado contendo dependências e bibliotecas necessárias.
- Este sistema de arquivos é imutável e conhecido como **imagem**.
- A partir da imagem, criam-se **containers** (instâncias em execução).
- A imagem é a representação estática da aplicação e sua configuração; o container é a execução em memória no host.

## Principais benefícios do Docker

Docker permite que usuários empacotem uma aplicação com todas as suas dependências em uma unidade padronizada (container) para desenvolvimento de software que poderá ser executado em ambientes distintos. Isso resolve:

- **Inconsistência de ambientes:** dev, staging e produção funcionam identicamente.
- **Isolamento:** cada app tem seu espaço isolado.
- **Portabilidade:** "funciona no meu computador" deixa de ser desculpa.
- **Escalabilidade:** fácil criar múltiplas instâncias paralelas.