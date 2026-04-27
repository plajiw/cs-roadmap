namespace ProjetoMVC.Models;

public class RepositorioProdutoDB : IRepositorioProduto
{
    private readonly AppDbContext _context;

    public RepositorioProdutoDB(AppDbContext context)
    {
        _context = context;
    }
    
    public List<Produto> ObterTodos()
    {
        return _context.Produtos.ToList();
    }

    public Produto? ObterPorFiltro(ProdutoFiltro filtro)
    {
        throw new NotImplementedException();
    }

    public void Adicionar(Produto produto)
    {
        throw new NotImplementedException();
    }

    public void Atualizar(Produto produto)
    {
        throw new NotImplementedException();
    }

    public void Remover(Guid id)
    {
        throw new NotImplementedException();
    }
}