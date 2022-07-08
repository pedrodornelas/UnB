<?php
    require('../system\backend\connect_db.php');
?>

<!DOCTYPE html>
<html lang="pt-br">

<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">

    <link href="https://use.fontawesome.com/releases/v5.0.6/css/all.css" rel="stylesheet">
    <link rel="stylesheet" href="https://stackpath.bootstrapcdn.com/bootstrap/4.4.1/css/bootstrap.min.css"
        integrity="sha384-Vkoo8x4CGsO3+Hhxv8T/Q5PaXtkKtu6ug5TOeNV6gBiFeWPGFN9MuhOf23Q9Ifjh" crossorigin="anonymous">
    <link rel="stylesheet" href="src/css/main.css">
    <link rel="stylesheet" href="src/css/sidebar.css">
    <link rel="icon" href="../src/icon.png">
    
    <title> Audio Alerta</title>
    
    <style>
        .tabela {
            margin-top: 30px;
        }
        
    </style>
    
    </head>
    
    <nav class="navbar navbar-dark bg-dark">
        <div class="container-fluid">
            <a class="navbar-brand" href="../">
            <img src="../src/back.jpg" alt="" width="20" height="30" class="d-inline-block align-text-top">
            Voltar para Dashboard
            </a>
        </div>
        </nav>
    
    <div class="container">
    
    <table class="table table-dark table-striped tabela">
        <thead>
            <tr>
            <th scope="col">Coletora</th>
            <th scope="col">Status Tiro</th>
            <th scope="col">Status Serra</th>
            <th scope="col">Lat</th>
            <th scope="col">Lng</th>
            <th scope="col">Data</th>
            </tr>
        </thead>
        <tbody>
         
    <?php
    
    $sql = "SELECT * FROM `dados` WHERE 1 ORDER BY `data` DESC";
    
    
    $resultado = mysqli_query($conn, $sql);
    
    if($resultado){
        while($registros = mysqli_fetch_array($resultado, MYSQLI_ASSOC)){

        $id = $registros['id_coletora'];
        $tiro = $registros['status_tiro']; 
        $serra = $registros['status_serra'];
        $lat =   $registros['latitude'];
        $lon =   $registros['longitude'];
        $data =   $registros['data'];
        
        echo '<tr>';
        echo '<th scope="row">'.$id.'</th>';
        echo '<td>'.$tiro.'</td>';
        echo '<td>'.$serra.'</td>';
        echo '<td>'.$lat.'</td>';
        echo '<td>'.$lon.'</td>';
        echo '<td>'.$data.'</td>';
        echo '</tr>';
        }
        
        
    }
    
    ?>
            
        </tbody>
    </table>
      
    </div>
      

    
</body>
</html>