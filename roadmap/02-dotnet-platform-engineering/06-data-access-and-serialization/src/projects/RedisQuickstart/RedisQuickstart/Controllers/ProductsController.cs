using Microsoft.AspNetCore.Mvc;
using RedisQuickstart.Models;
using RedisQuickstart.Services;

namespace RedisQuickstart.Controllers;

[ApiController]
[Route("api/[controller]")]
public class ProductsController : ControllerBase
{
    private readonly ProductService _service;

    public ProductsController(ProductService service) => _service = service;

    [HttpGet("{id}")]
    public async Task<IActionResult> Get(Guid id)
    {
        var product = await _service.GetProductAsync(id);
        return product != null ? Ok(product) : NotFound();
    }

    [HttpGet]
    public List<Product> GetAll()
    {
        var products = _service.GetAll();
        return products;
    }
}