 _____  ______          _____  __  __ ______ 
|  __ \|  ____|   /\   |  __ \|  \/  |  ____|
| |__) | |__     /  \  | |  | | \  / | |__   
|  _  /|  __|   / /\ \ | |  | | |\/| |  __|  
| | \ \| |____ / ____ \| |__| | |  | | |____ 
|_|  \_\______/_/    \_\_____/|_|  |_|______|

       +---------------------------------------+
       |Projecto de Laborat�rio de Computadores|
       |	  "Client e Server"            |
       |Jo�o Lucas Pires , up201606617@fc.up.pt|
       |Solange Perdig�o , up201603610@fc.up.pt|
       +---------------------------------------+
+---------------------------------------------------------------------------------------------------------------------------------+
|                                                                                                                                 |
|                                                                                                                                 |
|	Este projecto � constituido por dois programas: O servidor (supermercado) e o cliente (clientes).                         |
|	O servidor gere todo o servi�o de stocks, contas de utilizadores e acesso a estatisticas individuais e globais.           |
|	O programa cliente, permite cada utlizador aceder a v�rias funcionalidades, como efetuar compras, gerir o saldo , etc...  |
|                                                                                                                                 |
|                                                                                                                                 |
+---------------------------------------------------------------------------------------------------------------------------------+

Para obter os execut�veis:

Nas pastas que cont�m os c�digos-fonte, ao correr o comando 'make' no terminal cada execut�vel ser� criado automaticamente.
Em seguida, deve-se copiar ambos os execut�veis para uma pasta geral.
Por fim, deve-se copiar o script 'first.sh' para a pasta que cont�m os execut�veis
e execut�-lo de forma a criar os ficheiros que ir�o ser usados para guardar as informa��es dos programas.
Notas:
 1- Caso ao executar o script 'first.sh' se occorrer um erro de permiss�o, dever� executar o seginte comando: 'chmod 777 first.sh'
 2- Se ao executar o 'first.sh' ocorrer um erro de interpretador, dever� executar o seguinte comando: 'sed -i -e 's/\r$//' first.sh'
Ir�o ser criados tr�s ficheiros "product_db", "user_db", e "shoppinglist_db".
Para se poder utilizar o programa 'client' deve-se primeiro criar utilizadores e produtos para serem utilizados no 'client'.

------------------------------------------------------------------------------------------------------------------------------------------

Programa servidor:

Para aceder ao servidor, dever� colocar como senha 'fcup17'.
Ao entrar no menu inicial, aparecer� 4 op��es.

 -> 1� op��o: permite criar um novo utilizador (Cliente):
      - Nesta op��o ser� pedido o nome do cliente, o contacto, o username (caso j� exista um cliente com o mesmo username � pedido que introduza outro diferente), e por �ltimo a password, esta tem de ter pelo menos 5 caracteres e no m�ximo 20;

 -> 2� op��o: Gerir Stocks
      - 1�op��o: Adiconar um novo poduto:
             - � pedido o nome do produto, a quantidade, o pre�o de custo e o pre�o de venda (o pre�o de venda nunca pode ser inferiror ao pre�o de custo);
      - 2�op��o: Alterar atributos de um produto:
             - Selecioanr o c�digo do produto que deseja alterar, caso contr�rio pressiona 'q', para voltar ao menu anterior.
             - Para alterar a quantidade do produto, deve premir 1;
             - Para alterar o pre�o de custo, deve premir 2;
             - Para alterar o pre�o de venda, deve premir 3;
             - Para voltar ao menu anterior, prime 4;
       - 3�op��o: Eliminar o produto
             - Selecionar o c�digo do produto que deseja eliminar e depois confirmar se quer mesmo o eliminar preimindo 's'. Para cancelar basta premir outra tecla qualquer;
       - 4�op��o: voltar
             - Voltar par o menu principal do servidor;

 -> 3�op��o: Ver estat�sticas:
      - 1�op��o: Permite ver a quantidade e pre�o de venda total;
      - 2�op��o: Permite ver a quantidade vendida por produto, para isso basta inserir o c�digo do produto que deseja ver;
      - 3�op��o: Permite ver o lucro por produto, para isso basta inserir o c�digo do produto que deseja ver;
      - 4�op��o: Permite ver as compras por cliente, para isso basta inserir o c�digo do cliente que deseja ver;
      - 5�op��o: Volta para o menu principal do servidor;
            

 -> 4�op��o: Logout:
      - Sai do servidor;

-------------------------------------------------------------------------------------------

Programa Cliente:


Para aceder ao Cliente, dever� colocar o username e a password respetiva.
Ao entrar no menu inicial, aparecer� 4 op��es.

 -> 1�op��o: Gerir Saldo:
      - Permite acrescentar mais dinheiro � conta do utilizador;
      - Para adiconar mais dinheiro deve premir 's'ou 'n' para voltar par o menu anterior;

 -> 2�op��o: Inciar Compra:
      - Permite ao utilizador comprar produtos;
      - Para comprar um produto , basta inserir o c�digo do produto que deseja comprar.
      - Depois � pedido que introduza a quantidade que deseja, caso n�o exista a quantidade pretendida no Stock, o programa n�o deixa efetuar a compra. O mesmo acontece se n�o tiver saldo suficiente para efetuar a compra;
      - Para ver lista de compras, basta primir 'l';
      - Para terminar a compra, primir -1;

 -> 3�op��o: Ver Estat�sticas:
      - 1�op��o: Permite ver a quantidade total de produtos adquiridos;
      - 2�op��o: Permite ver a quantidade comprada de um determinado produto, para isso basta inserir o c�digo do produto que deseja ver;
      - 3�op��o: Permite ver o valor total gasto num determinado produto, para isso baste inserir o c�digo do produto que deseja ver;
      - 4�op��o: Permite voltar ao menu principal do CLiente;

 -> 4�op��o: Logout
     - Sai do programa;
