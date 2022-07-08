<?php
    require('system\backend\connect_db.php');
    header("Refresh: 60");
    date_default_timezone_set('America/Sao_Paulo');    
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
    <link rel="icon" href="src/icon.png">
    
    <title> Audio Alerta</title>
    
    <script src="https://code.jquery.com/jquery-3.4.1.slim.min.js"
        integrity="sha384-J6qa4849blE2+poT4WnyKhv5vZF5SrPo0iEjwBvKU7imGFAV0wwj1yYfoRSJoZ+n"
        crossorigin="anonymous"></script>
    <script src="https://cdn.jsdelivr.net/npm/popper.js@1.16.0/dist/umd/popper.min.js"
        integrity="sha384-Q6E9RHvbIyZFJoft+2mJbHaEWldlvI9IOYy5n3zV9zzTtmI3UksdQRVvoxMfooAo"
        crossorigin="anonymous"></script>
    <script src="https://stackpath.bootstrapcdn.com/bootstrap/4.4.1/js/bootstrap.min.js"
        integrity="sha384-wfSDF2E50Y2D1uUdj0O3uMBJnjuUD4Ih7YwaYd1iqfktj0Uod8GCExl3Og8ifwB6"
        crossorigin="anonymous"></script>
</head>

<body>

    <script>
        
        let map;
        let markersArray = [];

        function initMap() {
            map = new google.maps.Map(document.getElementById('map'), {
                center: { lat: -15.84, lng: -48.02 },
                zoom: 11.7
            });
            
            <?php
                $cont_t=0;
                $cont_s=0;
                $cont=0;
                                
                for ($i=1; $i < 5; $i++) { 
                                          
                    $sql = 'SELECT * FROM `dados` WHERE `id_coletora` = '.$i.' ORDER BY `data` DESC LIMIT 1';
                
                    $resultado = mysqli_query($conn, $sql);
                    
                    if($resultado){
                        while($registros = mysqli_fetch_array($resultado, MYSQLI_ASSOC)){

                        $id = $registros['id_coletora']; 
                        $tiro = $registros['status_tiro']; 
                        $serra = $registros['status_serra'];
                        $lat =   $registros['latitude'];
                        $lon =   $registros['longitude'];
                        $data =   $registros['data'];
                        
                        if($tiro){
                            $cor = "red";
                            $cont_t++;
                        }
                        else if($serra) {
                            $cor = "yellow";
                            $cont_s++;
                        }
                        else {
                            $cor = "green";
                            $cont++;
                        }
                            
                        echo 'addMarker({ lat: '.$lat.', lng: '.$lon.' }, "'.$cor.'");';
                    
                        }
                    }
                    
                }
                
                $sql = "SELECT * FROM `dados` WHERE 1 ORDER BY `data` DESC LIMIT 1";
                
                $resultado = mysqli_query($conn, $sql);
                
                if($resultado){
                    while($registros = mysqli_fetch_array($resultado, MYSQLI_ASSOC)){

                    $last = $registros['data'];
                    
                    }
                }
            
            ?>
        
        // addMarker({ lat: -15.84, lng: -48.02 }, "yellow");
        // addMarker({ lat: -15.82, lng: -47.87 }, "red");
        }
        
        

        function addMarker(latLng, color) {
            let url = "http://maps.google.com/mapfiles/ms/icons/";
            url += color + "-dot.png";

            let marker = new google.maps.Marker({
                map: map,
                position: latLng,
                icon: {
                    url: url,
                    scaledSize: new google.maps.Size(42, 42)
                },
            });

            markersArray.push(marker);
        }


    </script>

    <div class="page-wrapper chiller-theme toggled">
        <a id="show-sidebar" class="btn btn-sm btn-dark" href="#">
            <i class="fas fa-bars"></i>
        </a>
        
        <nav id="sidebar" class="sidebar-wrapper">
            <div class="sidebar-content">
                <div class="sidebar-brand">
                    <a href="#">Audio Alerta Dashboard</a>
                </div>
                
                <div class="sidebar-menu">
                    <ul>
                        <li>
                            <a href="#">Última atualização: <?php $last = explode(" ", $last); echo $last[1]; ?>
                            </a>
                        </li>
                        <li class="header-menu">
                            <span>Opções</span>
                        </li>
                        <li class="sidebar-collapse">
                            <a href="#">
                                <i class="fas fa-map"></i>
                                <span>Mapa</span>
                                <span class="badge badge-pill badge-danger">Alerta</span>
                            </a>
                        </li>
                        <li class="sidebar-collapse">
                            <a href="#">
                                <i class="fas fa-microchip"></i>
                                <span>Coletoras</span>
                                <span class="badge badge-pill badge-success">
                                <?php
                                
                                $contador = 0;
                                
                                for ($i=1; $i < 5; $i++) { 
                                                          
                                    $sql = "SELECT MAX(`data`) AS ultimo FROM `dados` WHERE `id_coletora`=".$i;
                                    $resultado = mysqli_query($conn, $sql);
        
                                    if($resultado){
                                        while($registros = mysqli_fetch_array($resultado, MYSQLI_ASSOC)){

                                        $ultimo = $registros['ultimo'];
                                        $date = new DateTime() ;

                                        (int)$date = $date->getTimestamp();
                                        
                                        (int)$data = strtotime($ultimo);
                                        
                                        if(($date - $data) < 60)
                                            $contador++;
                                        }
                                    }
                                }
                                
                                echo $contador." Online";
                                
                                ?>
                                </span>
                            </a>
                        </li>
                        <li class="sidebar-collapse">
                            <a href="./logs">
                                <i class="fas fa-history"></i>
                                <span>Histórico de alertas</span>
                            </a>
                        </li>
                        <!-- <li class="sidebar-collapse">
                            <a href="#">
                                <i class="fas fa-exclamation-triangle"></i>
                                <span>Fazer denúncia</span>
                            </a>
                        </li> -->
                        <li class="sidebar-collapse">
                            <a href="#" data-toggle="modal" data-target="#como-funciona">
                                <i class="fas fa-question-circle"></i>
                                <span >Como funciona</span>
                            </a>
                        </li>
                        
                        <li class="header-menu">
                            <span>Legenda</span>
                        </li>
                        <li>
                            <a href="#">Arma de fogo
                                <span class="badge badge-pill badge-danger"> <?php echo $cont_t; ?> </span>
                            </a>
                        </li>
                        <li>
                            <a href="#">Serra elétrica
                                <span class="badge badge-pill badge-warning"> <?php echo $cont_s; ?> </span>
                            </a>
                        </li>
                        <li>
                            <a href="#">Sem registro
                                <span class="badge badge-pill badge-success"> <?php echo $cont; ?> </span>
                            </a>
                        </li>
                        
                    </ul>
                    
                </div>
            </div>
        </nav>

        <div id="map"></div>

    </div>
    
    <script src="src/js/sidebar.js"></script>
    
    
    <div class="modal fade" id="como-funciona" tabindex="-1" role="dialog" aria-labelledby="como-funcionaTitle" aria-hidden="true">
            <div class="modal-dialog modal-dialog-centered" role="document">
                <div class="modal-content">
                    <div class="modal-header">
                        <h5 class="modal-title" id="exampleModalLongTitle">Como funciona?</h5>
                        <button type="button" class="close" data-dismiss="modal" aria-label="Close">
                            <span aria-hidden="true">&times;</span>
                        </button>
                    </div>
                    <div class="modal-body">
                        <p>
                            No mapa é possível ver alguns pontos, estes nos quais estão localizadas coletoras de áudio. Então, esses áudios são analisados em 
                            tempo real por meio de Machine-Learning e nos retornam se possivelmente temos barulhos de tiro ou serra elétrica.
                        </p>
                        <p>
                            Isto foi desenvolvido para que a denúncia pudesse ser feita automaticamente, ou mesmo por pessoas que pudessem estar utilizando a
                            dashboard em sua região, identificando por exemplo tiroteios, desmatamento, em que talvez não se tenha constante policiamento ou 
                            vigilância.
                        </p>
                        <p>
                            A dashboard é atualizada automaticamente, atualizando as informações sobre os barulhos coletados e a respectiva coletora muda sua 
                            cor conforme o barulho identificado, na legenda é possível ver qual cor representam os barulhos.
                        </p>
                    </div>
                    <div class="modal-footer">
                        <button type="button" class="btn btn-primary" data-dismiss="modal">Fechar</button>
                    </div>
                </div>
            </div>
        </div>
    
    
    <script async defer
        src="https://maps.googleapis.com/maps/api/js?key=AIzaSyBqaQyK9-mrXLfL_0h3_f8UW8Fto7Goqso&callback=initMap">
        </script>
    
</body>
</html>