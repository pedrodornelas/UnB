<?php
    $servidor = '192.185.210.165';
    $usuario = 'engne598';
    $senha = 'ges2019direx@)!(';
    $dbname = 'engne598_coletora_alerta_db';  

    $conn = mysqli_connect($servidor, $usuario, $senha, $dbname);
    
    if(!$conn){
        die("Falha na conexao: " . mysqli_connect_error());
    }else{
        // echo "Conexao realizada com sucesso";
    }      
?>