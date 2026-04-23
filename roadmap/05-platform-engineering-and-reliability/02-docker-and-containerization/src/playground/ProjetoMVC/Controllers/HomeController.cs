using System.Diagnostics;
using Microsoft.AspNetCore.Mvc;
using ProjetoMVC.Models;

namespace ProjetoMVC.Controllers
{
    public class HomeController : Controller
    {
        private readonly IRepositorioProduto _repositorioProduto;
        private readonly IHttpContextAccessor _httpContextAccessor;
        private string mensagem;

        public HomeController(IRepositorioProduto repositorioProduto, IHttpContextAccessor httpContextAccessor)
        {
            _repositorioProduto = repositorioProduto;
            _httpContextAccessor = httpContextAccessor;
            var hostname = _httpContextAccessor.HttpContext?.Request.Host.Value;
            mensagem = $"Olá, seja bem-vindo ao nosso site! Você está acessando a partir do host: {hostname}";
        }

        public IActionResult Index()
        {
            var produtos = _repositorioProduto.ObterProdutos();
            ViewBag.Mensagem = mensagem;
            return View(produtos);
        }
    }
}
