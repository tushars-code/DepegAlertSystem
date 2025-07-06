#include "../include/Config.hpp"

Config::Config() {
    coingecko_api_key = "CG-45Q75kQBEfyv7z5ZKitk4ve7";
    etherscan_api_key = "R6SAE2MMI2XVDZ1GBCP5HJDQH91623PM9M";
    news_api_key = "f9d8c468c6834f8a855192dc3ea8e228";
    thegraph_api_token = "eyJhbGciOiJLTVNFUzI1NiIsInR5cCI6IkpXVCJ9.eyJleHAiOjE3ODc4MDEyNzksImp0aSI6IjIwNmIwYWRjLTg4YWEtNGQwYi1hODA0LTA1MDAwNzljZDVkZiIsImlhdCI6MTc1MTgwMTI3OSwiaXNzIjoiZGZ1c2UuaW8iLCJzdWIiOiIwcXVidWUzMDgyZWY3NjFjYzIzNTEiLCJ2IjoxLCJha2kiOiI0NDQwMzg4ZDI4MzYyYjI1MDZiOTU0NTFjNDZlYWQ2MDNlZjE0ZWU0NmU1ZGUzYjdmOTgwZmQyMWI2NjU0ZTUzIiwidWlkIjoiMHF1YnVlMzA4MmVmNzYxY2MyMzUxIn0.arVQOOFX-zY7U5E9cdodcAayzcPHxHOiw7JUO0_ZZHYuevqu56wvl7uSijRUm48Lp0ZEJGLRgGIDeKn-XQP-pA";
    stablecoins = { "tether", "usdc", "dai" };
}
