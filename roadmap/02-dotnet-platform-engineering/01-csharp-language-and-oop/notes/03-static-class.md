# Static Class

## Classe Estática

Uma classe estática não pode ser instanciada e não pode ser herdada.

Em C#, uma classe estática é implicitamente `sealed` e `abstract` ao mesmo tempo:

- `sealed` porque não pode ser herdada.
- `abstract` porque não pode ser instanciada.

Apesar disso, ela não é usada como uma classe abstrata comum. O objetivo aqui é apenas representar um tipo que agrupa membros utilitários da aplicação.

## Regras de uma classe estática

Uma classe estática:

- Só pode conter membros estáticos.
- Pode conter métodos, propriedades, campos, eventos e construtor estático.
- Não pode conter membros de instância.
- Não pode implementar membros com `override`.

```cs
public static class MathHelper
{
	public static double Pi = 3.14159;

	public static int Sum(int a, int b)
	{
		return a + b;
	}
}
```

Uso:

```cs
var result = MathHelper.Sum(10, 20);
Console.WriteLine(MathHelper.Pi);
```

## Por que não faz sentido sobrescrita

Sobrescrita (`override`) existe para alterar comportamento polimórfico em objetos instanciados.

Como classes estáticas não possuem instâncias, não existe despacho polimórfico de instância. Por isso, métodos estáticos não podem ser `virtual`, `abstract` ou `override`.

## Quando usar

Classes estáticas costumam ser úteis para:

- Métodos utilitários.
- Funções puras e sem estado.
- Agrupamento de operações que não dependem de uma instância.

Se o comportamento depende de estado interno, colaboração entre objetos ou herança, normalmente uma classe estática não é a melhor escolha.