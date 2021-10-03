 _____  ______          _____  __  __ ______ 
|  __ \|  ____|   /\   |  __ \|  \/  |  ____|
| |__) | |__     /  \  | |  | | \  / | |__   
|  _  /|  __|   / /\ \ | |  | | |\/| |  __|  
| | \ \| |____ / ____ \| |__| | |  | | |____ 
|_|  \_\______/_/    \_\_____/|_|  |_|______|

       +---------------------------------------+
       |Projecto de Laboratório de Computadores|
       |	  "Client e Server"            |
       |João Lucas Pires , up201606617@fc.up.pt|
       |Solange Perdigão , up201603610@fc.up.pt|
       +---------------------------------------+
+---------------------------------------------------------------------------------------------------------------------------------+
|                                                                                                                                 |
|                                                                                                                                 |
|	Este projecto é constituido por dois programas: O servidor (supermercado) e o cliente (clientes).                         |
|	O servidor gere todo o serviço de stocks, contas de utilizadores e acesso a estatisticas individuais e globais.           |
|	O programa cliente, permite cada utlizador aceder a várias funcionalidades, como efetuar compras, gerir o saldo , etc...  |
|                                                                                                                                 |
|                                                                                                                                 |
+---------------------------------------------------------------------------------------------------------------------------------+

Para obter os executáveis:

Nas pastas que contém os códigos-fonte, ao correr o comando 'make' no terminal cada executável será criado automaticamente.
Em seguida, deve-se copiar ambos os executáveis para uma pasta geral.
Por fim, deve-se copiar o script 'first.sh' para a pasta que contém os executáveis
e executá-lo de forma a criar os ficheiros que irão ser usados para guardar as informações dos programas.
Notas:
 1- Caso ao executar o script 'first.sh' se occorrer um erro de permissão, deverá executar o seginte comando: 'chmod 777 first.sh'
 2- Se ao executar o 'first.sh' ocorrer um erro de interpretador, deverá executar o seguinte comando: 'sed -i -e 's/\r$//' first.sh'
Irão ser criados três ficheiros "product_db", "user_db", e "shoppinglist_db".
Para se poder utilizar o programa 'client' deve-se primeiro criar utilizadores e produtos para serem utilizados no 'client'.

------------------------------------------------------------------------------------------------------------------------------------------

Programa servidor:

Para aceder ao servidor, deverá colocar como senha 'fcup17'.
Ao entrar no menu inicial, aparecerá 4 opções.

 -> 1ª opção: permite criar um novo utilizador (Cliente):
      - Nesta opção será pedido o nome do cliente, o contacto, o username (caso já exista um cliente com o mesmo username é pedido que introduza outro diferente), e por último a password, esta tem de ter pelo menos 5 caracteres e no máximo 20;

 -> 2º opção: Gerir Stocks
      - 1ªopção: Adiconar um novo poduto:
             - É pedido o nome do produto, a quantidade, o preço de custo e o preço de venda (o preço de venda nunca pode ser inferiror ao preço de custo);
      - 2ªopção: Alterar atributos de um produto:
             - Selecioanr o código do produto que deseja alterar, caso contrário pressiona 'q', para voltar ao menu anterior.
             - Para alterar a quantidade do produto, deve premir 1;
             - Para alterar o preço de custo, deve premir 2;
             - Para alterar o preço de venda, deve premir 3;
             - Para voltar ao menu anterior, prime 4;
       - 3ªopção: Eliminar o produto
             - Selecionar o código do produto que deseja eliminar e depois confirmar se quer mesmo o eliminar preimindo 's'. Para cancelar basta premir outra tecla qualquer;
       - 4ªopção: voltar
             - Voltar par o menu principal do servidor;

 -> 3ªopção: Ver estatísticas:
      - 1ªopção: Permite ver a quantidade e preço de venda total;
      - 2ªopção: Permite ver a quantidade vendida por produto, para isso basta inserir o código do produto que deseja ver;
      - 3ªopção: Permite ver o lucro por produto, para isso basta inserir o código do produto que deseja ver;
      - 4ªopção: Permite ver as compras por cliente, para isso basta inserir o código do cliente que deseja ver;
      - 5ªopção: Volta para o menu principal do servidor;
            

 -> 4ªopção: Logout:
      - Sai do servidor;

-------------------------------------------------------------------------------------------

Programa Cliente:


Para aceder ao Cliente, deverá colocar o username e a password respetiva.
Ao entrar no menu inicial, aparecerá 4 opções.

 -> 1ªopção: Gerir Saldo:
      - Permite acrescentar mais dinheiro à conta do utilizador;
      - Para adiconar mais dinheiro deve premir 's'ou 'n' para voltar par o menu anterior;

 -> 2ªopção: Inciar Compra:
      - Permite ao utilizador comprar produtos;
      - Para comprar um produto , basta inserir o código do produto que deseja comprar.
      - Depois é pedido que introduza a quantidade que deseja, caso não exista a quantidade pretendida no Stock, o programa não deixa efetuar a compra. O mesmo acontece se não tiver saldo suficiente para efetuar a compra;
      - Para ver lista de compras, basta primir 'l';
      - Para terminar a compra, primir -1;

 -> 3ªopção: Ver Estatísticas:
      - 1ªopção: Permite ver a quantidade total de produtos adquiridos;
      - 2ªopção: Permite ver a quantidade comprada de um determinado produto, para isso basta inserir o código do produto que deseja ver;
      - 3ªopção: Permite ver o valor total gasto num determinado produto, para isso baste inserir o código do produto que deseja ver;
      - 4ªopção: Permite voltar ao menu principal do CLiente;

 -> 4ªopção: Logout
     - Sai do programa;
