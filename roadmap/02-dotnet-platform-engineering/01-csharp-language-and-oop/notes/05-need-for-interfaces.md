# Need for Interfaces

## O que são interfaces

Interfaces definem um contrato.

Elas dizem quais membros um tipo deve expor, mas não representam necessariamente uma implementação base concreta.

Uma interface é útil quando queremos descrever capacidade, comportamento esperado ou papel de um tipo, sem afirmar que os tipos envolvidos pertencem à mesma hierarquia de herança.

Em termos conceituais:

- Herança entre classes normalmente expressa uma relação do tipo "é um".
- Interface normalmente expressa uma relação do tipo "se comporta como" ou "é capaz de".

Por isso, interfaces são muito úteis quando tipos diferentes precisam oferecer o mesmo comportamento, mesmo sem compartilharem a mesma classe base.

## Características principais

Uma interface:

- Não pode ser instanciada diretamente.
- Define um contrato que outros tipos devem implementar.
- Pode ser implementada por classes, structs e records.
- Permite que tipos sem relação de herança direta sejam tratados de forma uniforme.

Historicamente, interfaces eram compostas apenas pela assinatura dos membros. Em versões mais novas do C#, interfaces também podem ter implementação padrão em alguns casos, mas a ideia principal continua sendo a definição de contrato.

## Por que classes abstratas nem sempre resolvem

Classes abstratas funcionam bem quando existe uma hierarquia real entre os tipos e quando faz sentido compartilhar estado ou implementação.

Mas elas não resolvem bem cenários em que:

- Os tipos já pertencem a hierarquias diferentes.
- Queremos compartilhar apenas capacidade, e não identidade de tipo.
- Precisamos que um mesmo tipo participe de mais de um contrato.

Esse é um dos principais motivos da existência de interfaces.

## Exemplo da necessidade de interfaces

Suponha que existam tipos diferentes no sistema que podem ser serializados.

```cs
public class Invoice
{
    public decimal Total { get; set; }
}

public class AuditLog
{
    public DateTime CreatedAt { get; set; }
}
```

Esses dois tipos não necessariamente possuem uma relação natural de herança entre si. Ainda assim, ambos podem precisar oferecer a capacidade de serialização.

Se tentássemos resolver isso apenas com classe abstrata, teríamos que forçar uma hierarquia artificial.

Com interface, podemos modelar o contrato diretamente:

```cs
public interface ISerializable
{
    string Serialize();
}

public class Invoice : ISerializable
{
    public decimal Total { get; set; }

    public string Serialize()
    {
        return $"Invoice: {Total}";
    }
}

public class AuditLog : ISerializable
{
    public DateTime CreatedAt { get; set; }

    public string Serialize()
    {
        return $"AuditLog: {CreatedAt:O}";
    }
}
```

Agora podemos tratar objetos diferentes de forma uniforme:

```cs
var items = new List<ISerializable>
{
    new Invoice { Total = 150.75m },
    new AuditLog { CreatedAt = DateTime.UtcNow }
};

foreach (var item in items)
{
    Console.WriteLine(item.Serialize());
}
```

Esse é um bom exemplo da necessidade de interfaces: tipos diferentes, sem a mesma classe base, podem ser tratados pelo mesmo contrato.

## Regras importantes

Interfaces seguem algumas regras importantes:

- Um tipo pode implementar várias interfaces.
- Uma classe pode herdar de apenas uma classe base.
- Uma interface pode herdar de uma ou mais interfaces.
- Ao implementar uma interface, o tipo precisa fornecer os membros exigidos pelo contrato, salvo casos de implementação padrão na própria interface.

Exemplo:

```cs
public interface IReadable
{
    string Read();
}

public interface IWritable
{
    void Write(string content);
}

public class FileDocument : IReadable, IWritable
{
    public string Read()
    {
        return "Conteudo do arquivo";
    }

    public void Write(string content)
    {
        Console.WriteLine(content);
    }
}
```

Nesse caso, `FileDocument` implementa dois contratos diferentes.

## Interfaces e múltiplos contratos

Esse é um ponto central: interfaces permitem múltiplos contratos.

Uma classe não pode herdar de duas classes base, mas pode implementar várias interfaces. Isso evita a necessidade de múltipla herança de classes para representar diferentes capacidades.

## Sobre o problema do diamante

No contexto tradicional de herança múltipla entre classes, existe o problema do diamante, em que um tipo pode herdar a mesma implementação por caminhos diferentes.

Como C# não permite herança múltipla de classes, esse problema já é evitado nesse nível.

Interfaces ajudam justamente porque permitem múltiplos contratos sem exigir múltipla herança de implementação entre classes.