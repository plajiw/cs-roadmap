namespace ProjetoMVC.Models;

public interface IRepositorioProduto
{
    List<Produto> ObterTodos();
    Produto? ObterPorFiltro(ProdutoFiltro filtro);
    void Adicionar(Produto produto);
    void Atualizar(Produto produto);
    void Remover(Guid id);
}