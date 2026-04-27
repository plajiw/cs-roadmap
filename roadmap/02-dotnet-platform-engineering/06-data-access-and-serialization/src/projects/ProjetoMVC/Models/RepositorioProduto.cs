namespace ProjetoMVC.Models;

public class RepositorioProduto : IRepositorioProduto
{
    private static readonly Dictionary<Guid, Produto> _produtos = new();

    static RepositorioProduto()
    {
        AdicionarProduto("Notebook", "Eletrônicos", "Notebook para estudos", 3500);
        AdicionarProduto("Mouse", "Acessórios", "Mouse gamer", 150);
    }
    
    private static void AdicionarProduto(string nome, string categoria, string descricao, decimal preco)
    {
        var produto = new Produto(nome, categoria, descricao, preco);
        _produtos.Add(produto.Id, produto);
    }
    
    public List<Produto> ObterTodos()
    {
        return _produtos.Values.ToList();
    }

    public Produto? ObterPorFiltro(ProdutoFiltro filtro)
    {
        filtro ??= new ProdutoFiltro();
        
        var query = _produtos.Values.AsQueryable();

        if (filtro.ComId.HasValue)
            query = query.Where(p => p.Id == filtro.ComId.Value);
        
        if (!string.IsNullOrWhiteSpace(filtro.ComNome))
            query = query.Where(p => p.Nome.ToLower().Contains(filtro.ComNome.ToLower()));
        
        if (!string.IsNullOrWhiteSpace(filtro.ComCategoria))
            query = query.Where(p => p.Categoria.ToLower().Contains(filtro.ComCategoria.ToLower()));
        
        if (!string.IsNullOrWhiteSpace(filtro.ComDescricao))
            query = query.Where(p => p.Descricao.ToLower().Contains(filtro.ComDescricao.ToLower()));
        
        if (filtro.ComPreco.HasValue)
            query = query.Where(p => p.Preco == filtro.ComPreco.Value);

        return query.FirstOrDefault();
    }

    public void Adicionar(Produto produto)
    {
        ArgumentNullException.ThrowIfNull(produto);

        _produtos.Add(produto.Id, produto);    
    }

    public void Atualizar(Produto produto)
    {
        ArgumentNullException.ThrowIfNull(produto);
        
        if (_produtos.TryGetValue(produto.Id, out var prod))
            _produtos[produto.Id] = prod;
    }

    public void Remover(Guid id)
    {
        if (id == Guid.Empty)
            throw new ArgumentException("Id inválido.");

        if (!_produtos.Remove(id))
            throw new KeyNotFoundException("Produto não encontrado.");
    }
}