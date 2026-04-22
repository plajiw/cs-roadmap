namespace ProjetoMVC.Models
{
    public interface IRepositorioProduto
    {
        IEnumerable<Produto> ObterProdutos();
    }
}
