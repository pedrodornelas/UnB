# Instruções

Para responder às questões que seguem, utilizem a seguinte notação:

1. letras minúsculas para nomes de variáveis: `x, y, ...`;
2. letras maiúsculas para nomes de funções: `AND, OR, ADD, ...`;
3. `\` representando o caracter lambda (λ): `\x = λx`;
4. `->` para introduzir o corpo de uma abstração lambda: `\x -> x`;
5. `=` para nomear expressões como fizemos na aula: `ID = x -> x`.

Várias perguntas são muitos mais simples e fáceis do que parecem, pare e pense! Explique o racional da sua solução: escreva como você pensou para construir a solução.


# Lógica booleana

Definimos os valores lógicos da seguinte forma:

```haskell
True  = \x y -> x
False = \x y -> y
```

Também definimos uma função auxiliar `IF` que facilita a construção de outras funções que envolvam valores lógicos.

```haskell
IF = \b x y -> b x y
```

**Item 1)** Construa uma definição para a função `XOR` que calcula o ou-exclusivo entre duas variáveis lógicas. Mostre que a sua função se comporta adequadamente calculando a saída para todas as possibilidades de entradas.

## Resposta Item 1)
---

Para responder o item eu pensei analisando a tabela verdade da porta XOR na tentativa de montar uma expressão `IF ELSE` para esta porta e então traduzir esta ideia em um código em cálculo-λ.

XOR:

| A | B | XOR |
| --- | --- | :---: |
| 0 | 0 | 0 |
| 0 | 1 | 1 |
| 1 | 0 | 1 |
| 1 | 1 | 0 |

Então eu montei a tabela verdade e tentei montar uma expressão da seguinte maneira:

```
IF A THEN (NOT B) ELSE B
```

Note que esta expressão representa bem a porta XOR, e então eu tentei transformar agora em cálculo-λ utilizando as expressões que fizemos para o IF e NOT:
```haskell
NOT = \b -> b False True
IF = \b x y -> b x y
XOR = \a c -> (\b x y -> b x y) a (NOT c) c
    = \a c -> (\b x y -> b x y) a ((\b -> b False True) c) c 
    --Fazendo redução beta
    = \a c -> (\b x y -> b x y) a (c False True) c
    = \a c -> (\x y -> a x y) (c False True) c
    = \a c -> (\y -> a (c False True) y) c
    --Chegamos em uma forma mais simplificada
XOR = \a c -> a (c False True) c
```

Para validá-la, vamos calcular as saídas para todos os casos

```haskell
XOR False False = (\a c -> a (c False True) c) False False
                = (\c -> False (c False True) c) False
                = False (False False True) False
                = (\x y -> y) (False False True) False
                = (\y -> y) False
                = False
```
```haskell
XOR False True = (\a c -> a (c False True) c) False True
               = (\c -> False (c False True) c) True
               = False (True False True) True
               = (\x y -> y) (False False True) True
               = (\y -> y) True
               = True
```
```haskell
XOR True False = (\a c -> a (c False True) c) True False
               = (\c -> True (c False True) c) False
               = True (False False True) False
               = (\x y -> x) (False False True) False
               = (\y -> (False False True)) True
               = False False True
               = (\x y -> y) False True
               = (\y -> y) True
               = True
```
```haskell
XOR True True = (\a c -> a (c False True) c) True True
              = (\c -> True (c False True) c) True
              = True (True False True) True
              = (\x y -> x) (True False True) True
              = True False True
              = (\x y -> x) False True
              = False
```

Assim foi possível concluir que a função funcionou perfeitamente para todos os casos.

# Registros (tuplas)

Definimos a função `PAIR = \x y -> (\b -> b x y)` que recebe dois dados e constrói uma tupla com eles. A API dessa estrutura envolve duas funções para acessar novamente os dados originais, i.e., extrair os dados da estrutura:

```haskell
FST = \p -> p True
SND = \p -> p False
```

**Item 2)** Defina uma função `SWAP` que recebe uma tupla e troca a posição dos seus elementos, isto é, `SWAP (PAIR a b) = PAIR b a`.

## Resposta Item 2)
---

Para tentar criar a função SWAP eu pensei como ela deveria funcionar, e tentei montar uma expressão para tentar representar minha ideia primeiro:

```haskell
SWAP (PAIR A B) = PAIR B A
```

Esta deveria ser a saída esperada, e então eu pensei em como eu poderia fazer para obter o B e o A, daí utilizando as funções `FST`, `SND` e `PAIR`,  pensei na função `SWAP` teria de receber o par e entregar um par trocado:

```haskell
SWAP = \p -> PAIR (SND p) (FST p)
```

Vamos neste momento tentar fazer a aplicação para ver se faz sentido a expressão montada:

```haskell
SWAP (PAIR x y) = (\p -> PAIR (SND p) (FST p)) (PAIR x y)
                = (\p -> PAIR (SND p) (FST p)) ((\x y -> (\b -> b x y)) x y)
                = (\p -> PAIR (SND p) (FST p)) (\b -> b x y)
                = PAIR ((\p -> p False) (\b -> b x y)) ((\p -> p True) (\b -> b x y))
                = PAIR (((\b -> b x y) False)) (((\b -> b x y) True))
                = PAIR (False x y) (True x y)
SWAP (PAIR x y) = PAIR y x
```

Note que foi utilizado diretamente assim como provado nos itens anteriores para False e True para facilitar. Note também que funcionou perfeitamente a expressão que utilizamos para que fosse possível executar a função `SWAP`.


**Item 3)** Defina uma função `MAP` que recebe uma tupla `p` e uma função `f` e aplica a função a cada um dos elementos da tupla, isto é, `MAP (PAIR a b) f = PAIR (f a) (f b)`.

## Resposta Item 3)
---

Para fazermos este item vamos utilizar alguns conceitos que utilizamos no item passado, da mesma maneira comecei pensando no que minha função MAP deveria me entregar de uma maneira resumida:

```haskell
MAP (PAIR a b) f = PAIR (f a) (f b)
```

Analisando esta expressão acima tentei pensar em expressão válida da seguinte maneira, pensando que a função MAP deve receber o par e também uma função genérica que irá ser aplicada ao par:
```haskell
MAP = \p f -> PAIR (f (FST p)) f( (SND p))
```

Vamos testar essa função com uma função `g` genérica, já utilizando as funções `FST` e `SND` diretamente:

```haskell
MAP (PAIR x y) g = (\p f -> PAIR (f (FST p)) (f (SND p))) (PAIR x y) g
                 = (\f -> PAIR (f (FST (PAIR x y))) (f (SND (PAIR x y)))) g
                 = PAIR (g x) (g y)
```

Note que chegamos exatamente ao que queríamos.

# Números naturais

Definimos os números naturais utilizando a codificação de Church:

```haskell
ZERO = \f x -> x
UM   = \f x -> f x
DOIS = \f x -> f (f x)
TRES = \f x -> f (f (f x))
... 
```

**Item 4)** Considerando a função `ADD = \n m -> (n INC) m`, verifique que `ADD ZERO DOIS = DOIS`, `ADD DOIS ZERO = DOIS`, isto é, `ZERO` é o elemento neutro a da soma como esperarado.

## Resposta Item 4)
---

Para verificar basta montarmos a expressão e realizar reduções beta até chegar em algo que represente a saída da computação, então:

```haskell
ADD ZERO DOIS = (\n m -> (n INC) m) ZERO DOIS
              = (\m -> (ZERO INC) m) DOIS
              = (ZERO INC) DOIS
              = ((\f x -> x) INC) DOIS
              = (\x -> x) DOIS
              = DOIS
```
```haskell
ADD DOIS ZERO = (\n m -> (n INC) m) DOIS ZERO
              = (DOIS INC) ZERO
              = ((\f x -> f(f x)) INC) ZERO
              = (\x -> INC(INC x)) ZERO
              = INC(INC ZERO)
              = \f x -> f ((INC ZERO) f x)
              = \f x -> f ((\f x -> f ((ZERO) f x)) f x)
              = \f x -> f ((\f x -> f ((\f x -> x) f x)) f x)
              = \f x -> f ((\f x -> f ((\x -> x) x)) f x)
              = \f x -> f ((\f x -> f x) f x)
              = \f x -> f (f x)
              = DOIS
```

Assim provamos que o `ZERO` tem influência neutra em ambas as expressões como esperado.

# Recursão

Para construir funções recursivas (que realizam repetição de algum processo) definimos o combinador `Y` da seguinte forma:

```haskell
P = (\x -> f (x x)) (\x -> f (x x))

Y = \f -> P
  = \f -> (\x -> f (x x)) (\x -> f (x x))
```

Na aula provamos que `P` é um ponto fixo de qualquer função `f`, isto é, `f P = P` para qualquer `f`. Esse fato é peça-chave para analisar função construídas a partir do combinador `Y`. 

**Item 5)** Seguindo a mesma metodologia das notas de aula, construa a função `FIBO = \n -> ...` que recebe um número natural `n` e retorna o n-ésimo elemento da sequência de Fibonacci. Os dois primeiros termos da sequência de Fibonacci são 1 e os demais são gerados pela soma dos dois anteriores, isto é, `[1,1,2,3,5,8,12,...]` e `Y FIBO 1 = 1`, `Y FIBO 6 = 8`, etc. Calcule `Y FIBO 4` para mostrar que a sua função funciona adequadamente.

## Resposta Item 5)
---

Para a resolução da questão eu tentei estudar como o combinador `Y` atua dentro do cálculo-λ, pois é uma abstração para o ponto fixo(`P = f P`), estudei o seguinte exempo:

```haskell
Y factorial 3 = factorial (Y factorial) 3
```

Isto só é possível graças à propriedade do ponto fixo de uma função qualquer, assim como definimos anteriormente. Logo, podemos começar a montar algo para montar uma função de FIBO:

```haskell
FIBO = \n -> IF(n==1) THEN 1 ELSE (FIBO (n-1)) ADD (FIBO (n-2)) --abstraindo a função para utilizar o combinador Y
FIBO = \f n -> IF(n==1) THEN 1 ELSE (f (n-1)) ADD (f (n-2))
```

Para tentar provar tentei fazer o primeiro e o segundo caso, `Y FIBO 1` e `Y FIBO 2`:
```haskell
Y FIBO 1 = FIBO (Y FIBO) 1
         = (\f n -> IF(n==1) THEN 1 ELSE (f (n-1)) ADD (f (n-2))) (Y FIBO) 1
         = IF(1==1) THEN 1 ELSE (Y FIBO 0) ADD (Y FIBO -1) --entra no if
         = 1
Y FIBO 2 = FIBO (Y FIBO) 2
         = (\f n -> IF(n==1) THEN 1 ELSE (f (n-1)) ADD (f (n-2))) (Y FIBO) 2
         = IF(2==1) THEN 1 ELSE (Y FIBO 1) ADD (Y FIBO 0) --não entra no if
         --a computação iria quebrar aqui
```

Como vemos acima, fazendo desta forma, a computação nunca iria acabar, iria continuar até quebrar a memória, enfim, então, precisei pensar em algo para resolver isto:

```haskell
FIBO = \f n -> IF(n==1 || n==2) THEN 1 ELSE (f (n-1)) ADD (f (n-2))
```

Para vermos se funcionará, vamos fazer os mesmos exemplos:
```haskell
Y FIBO 1 = FIBO (Y FIBO) 1
         = (\f n -> IF(n==1 || n==2) THEN 1 ELSE (f (n-1)) ADD (f (n-2))) (Y FIBO) 1
         = IF(1==1 || 1==2) THEN 1 ELSE (Y FIBO 0) ADD (Y FIBO -1) --entra no if
         = 1
Y FIBO 2 = FIBO (Y FIBO) 2
         = (\f n -> IF(n==1 || n==2) THEN 1 ELSE (f (n-1)) ADD (f (n-2))) (Y FIBO) 2
         = IF(2==1 || 2==2) THEN 1 ELSE (Y FIBO 1) ADD (Y FIBO 0) --entra no if
         = 1
```

Agora a computação dá certo pois ela entra no `IF` e se encerra corretamente. Fazendo então o caso pedido no exercício:
```haskell
Y FIBO 4 = FIBO (Y FIBO) 4
         = (\f n -> IF(n==1 || n==2) THEN 1 ELSE (f (n-1)) ADD (f (n-2))) (Y FIBO) 4
         = IF(4==1 || 4==2) THEN 1 ELSE (Y FIBO 3) ADD (Y FIBO 2) --vou deixar em suspenso para fazer separado cara uma das expressões do ADD
Y FIBO 3 = FIBO (Y FIBO) 3
         = (\f n -> IF(n==1 || n==2) THEN 1 ELSE (f (n-1)) ADD (f (n-2))) (Y FIBO) 3
         = IF(3==1 || 3==2) THEN 1 ELSE (Y FIBO 2) ADD (Y FIBO 1) --aqui podemos reduzir pois já sabemos Y FIBO 2 e Y FIBO 1
         = 1 ADD 1 = DOIS
--Voltando
Y FIBO 4 = (Y FIBO 3) ADD (Y FIBO 2)
         = DOIS ADD UM
         = TRES
```

Mostrando que o algorítmo dá certo.