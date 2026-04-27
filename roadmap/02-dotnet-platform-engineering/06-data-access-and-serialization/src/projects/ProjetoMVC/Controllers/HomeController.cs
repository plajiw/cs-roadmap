using System.Diagnostics;
using Microsoft.AspNetCore.Mvc;
using ProjetoMVC.Models;

namespace ProjetoMVC.Controllers;

public class HomeController : Controller
{
    private  readonly IRepositorioProduto _repositorioProduto;

    public HomeController(IRepositorioProduto repositorioProduto)
    {
        _repositorioProduto = repositorioProduto;
    }
    
    public IActionResult Index()
    {
        var produtos = _repositorioProduto.ObterTodos();
        return View(produtos);
    }
    
    [HttpPost]
    public IActionResult AdicionarProduto(string nome, string categoria, string descricao, decimal preco)
    {
        var produto = new Produto(nome, categoria, descricao, preco);
        _repositorioProduto.Adicionar(produto);

        return RedirectToAction("Index");
    }
    
    [HttpPost]
    public IActionResult RemoverProduto(Guid id)
    {
        _repositorioProduto.Remover(id);
        return RedirectToAction("Index");
    }

    public IActionResult Produtos(ProdutoFiltro filtro)
    {
        if (filtro.ComNome == null && filtro.ComCategoria == null && filtro.ComDescricao == null && !filtro.ComPreco.HasValue)
        {
            var todos = _repositorioProduto.ObterTodos();
            return View("Index", todos);
        }

        var resultado = _repositorioProduto.ObterPorFiltro(filtro);
    
        var listaResultado = new List<Produto>();
        
        if (resultado != null) 
            listaResultado.Add(resultado);

        return View("Index", listaResultado);
    }
}