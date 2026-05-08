FROM mcr.microsoft.com/dotnet/aspnet:8.0 AS base
LABEL version="1.0.3" description="Projeto MVC"
COPY dist /app
WORKDIR /app
EXPOSE 80/tcp
ENTRYPOINT ["dotnet", "ProjetoMVC.dll"]