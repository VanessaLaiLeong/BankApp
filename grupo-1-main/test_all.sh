#!/bin/bash
# File:  test_all.sh
# Author:  Vitor Custódio
# Created on:  21fev2020

DIFF="diff --ignore-space-change --ignore-blank-lines"
pass=0
nopass=0
make clean
make
prog_make=$?
if [ ${prog_make} != 0 ]; then
    echo "ERRO: Erro de compilação"
    exit 1
else
    echo "OK:Programa corretamente compilado...."
fi

exefile="banco_app"
if [ ! -f "${exefile}" ]; then
    echo "ERRO: Ficheiro executável ${exefile} não encontrado!"
    exit 1
else
    echo "**********************************"
    echo "******* TESTES AUTOMÁTICOS *******"
    echo "**********************************"
fi

for test_in in testes/t*_*.in ; do
    test_out="${test_in%.in}.out"
    stamp="${RANDOM}${RANDOM}"
    student_out=./studentOut/in_${stamp}
    ./${exefile} <${test_in} | sed -e 's/\r$//' >${student_out}
    rv_student=$?
    if [ ! -f "${student_out}" ]; then
        echo "ERRO: O output do Exercício não foi criado (file ${student_out})!"
        exit 1
    fi
    if [ ${rv_student} != 0 ]; then
        echo "ERRO: Programa executado com erros!"
        echo "REVEJA O CÓDIGO"
        rm -f ${student_out}
        exit 1
    fi
    
    ${DIFF} ${student_out} ${test_out} &>/dev/null
    rv_diff=$?
    rm -f ${student_out}

    if [ ${rv_diff} == 0 ]; then
        ((pass=pass+1))
        echo -e "->\e[92mTeste ${test_in}:-> SUCESSO! \e[0m"
    else
        ((nopass=nopass+1))
        echo -e "->\e[31mTeste ${test_in}:-> NÃO PASSOU. REVEJA O CÓDIGO! \e[0m"
    fi
done
echo "**********************************"
echo "**** Fim de Testes Automáticos ***"
echo -e "**********\e[92m Testes OK: ${pass} \e[0m**********"
echo -e "*********\e[31m Testes NOK: ${nopass} \e[0m*********"
echo "**********************************"
echo "Lembre-se que estes testes não cobrem todos os casos."
echo "É da responsabilidade do programador testar exaustivamente a aplicação!!!!"
echo "Pode adicionar testes ou testar manualmente os casos descritos no enunciado"
echo "A efetuar make clean"
make clean
