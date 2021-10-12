[x]Leia do teclado o nome do arquivo de áudio a ser aberto. Esse arquivo será aberto em modo leitura de arquivo binário.

[] Leia do teclado o número de coeficientes que devem ser utilizados na compressão.

[] Leia todo o conteúdo do arquivo e armazene em um vetor de unsigned char dinamicamente alocado (memória heap), ou seja, cada sample do arquivo de áudio é retratado por um inteiro de 8 bits sem sinal. Uma função será dada para fazer esta leitura dos dados.

[] Em seguida, considere esse vetor de dados/samples como entrada para a Transformada Discreta de Fourier, ou seja, a partir deles será produzido um vetor de coeficientes
do tipo double complex dinamicamente alocado.

[] Em seguida ordene o vetor de coeficientes de maneira decrescente segundo suas magnitudes, ou seja, o coeficiente de maior magnitude será o primeiro do vetor e o de menor magnitude, o último. Será preciso, no entanto, guardar qual é a posição original
de cada coeficiente, pois essa informação será usada nos próximos passos.

[] Atribua zero aos coeficientes das posições igual e maiores do que T. Devem ser mantidos no vetor de coeficientes somente os valores dos T primeiros coeficientes.

[] Em seguida, volte os coeficientes para suas posições originais, ou seja, para as posições que eles tinham antes da ordenação.

[] Utilizando como entrada os coeficientes processados (obtidos no passo anterior), aplique a Transformada Inversa de Fourier. Note que a Inversa poderá gerar valores de ponto flutuante, que deverão, na hora da escrita, serem convertidos para inteiros.

[] Salve o resultado dessa Transformada Inversa em um arquivo binário de áudio em que as amplitudes do diafragma são formadas por 8 bits sem sinal. Não esqueça de copiar para o novo arquivo o cabeçalho do arquivo original, esse corresponde aos primeiros 44
bytes do arquivo.

[] O programa deverá mostrar como saída:

- O número de observações(samples) lidas do arquivo de áudio (primeira linha);
- O número de valores menores ou iguais a zero tanto na parte real quanto na parte imaginária no vetor dos coeficientes original (antes da atribuição de 0 para os valores de posições maiores e iguais a T) (segunda linha);
- A sequência ordenada das magnitudes dos T primeiros coeficientes, convertidas para um inteiro (casting para int) (terceira linha em diante).
