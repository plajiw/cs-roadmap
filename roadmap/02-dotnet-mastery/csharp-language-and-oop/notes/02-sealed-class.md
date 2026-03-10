# Sealed Class

## Modificador Sealed

`sealed` é um modificador que impede que uma classe seja herdada.

```cs
public sealed class PaymentService
{
}

public class CustomPaymentService : PaymentService
{
} // Erro de compilação
```

O objetivo principal de `sealed` normalmente não é desempenho, e sim deixar explícito que aquele tipo não deve ser estendido.

Isso pode ser útil quando:

- A classe já representa uma implementação final.
- Herdar daquele tipo poderia quebrar regras de negócio ou invariantes.
- A API foi desenhada para composição, e não para herança.

## Sealed em métodos

Também é possível usar `sealed` em métodos sobrescritos. Nesse caso, o método deixa de poder ser sobrescrito novamente em classes mais derivadas.

Isso só faz sentido em métodos `override`.

```cs
public class BaseClass
{
    public virtual string GetMessage()
    {
        return "Base";
    }
}

public class DerivedClass : BaseClass
{
    public sealed override string GetMessage()
    {
        return "Derived";
    }
}

public class FinalClass : DerivedClass
{
    public override string GetMessage()
    {
        return "Final";
    }
} // Erro de compilação
```

Aqui, `DerivedClass` ainda pode ser herdada. O que foi selado foi apenas o método `GetMessage()`.

## Exemplo da biblioteca padrão

A classe `string` é um exemplo clássico de classe selada.

```cs
public class MyStringClass : string
{
} // Erro de compilação
```

Selar tipos como `string` ajuda a preservar o comportamento esperado do tipo e evita cenários em que herança poderia introduzir inconsistências.

## Observação sobre desempenho

Em alguns cenários, `sealed` pode permitir pequenas otimizações, mas isso costuma ser um efeito secundário.

Na prática, o motivo principal para usar `sealed` deve ser modelagem e intenção de design.