namespace ProjetoMVC.Models;

public class ProdutoFiltro
{
    public Guid? ComId { get; set; }
    public string? ComNome  { get; set; }
    public string? ComCategoria  { get; set; }
    public string? ComDescricao  { get; set; }
    public decimal? ComPreco  { get; set; }
}