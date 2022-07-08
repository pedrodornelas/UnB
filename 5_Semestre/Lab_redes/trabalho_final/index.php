<?php
    require('consulta.php');
?>
<!DOCTYPE html>
<html>
    <head>
        <title>WebService</title>
        <meta http-equiv="Content-Type" content="text/html; charset=UTF-8"/>
        <meta http-equiv="X-UA-Compatible" content="IE=edge"/>
        <link rel="stylesheet" type="text/css" href="style.css"/>
        <script type="text/javascript" src="https://www.gstatic.com/charts/loader.js"></script>
    </head>
    <body>
        <div class="titulo">
            <h1>WebService</h1>
        </div>

        <form class="input" action="index.php" method="GET">
            <label class="item" for="valor">Digite o CEP:</label>
            <input class="item" type="text" id="cep" name="cep" placeholder="71000000"/>
            <input class="item" type="submit" value="Enviar">
        </form>
        <?php
            if($aux_cep!=0){
                if($status_cep=="OK"){
                    echo '<h2>Endereço: </h2>';
                    echo '<p class="item">';
                    echo "CEP: ".$resp_cep->cep;
                    echo " - Estado: ".$resp_cep->state;
                    echo " - Cidade: ".$resp_cep->city;
                    echo " - Bairro: ".$resp_cep->neighborhood;
                    echo " - Rua: ".$resp_cep->street;
                    echo "</p>";
                }
                else{
                    echo '
                    <script>
                        alert("Digite um CEP válido!");
                    </script>
                    ';
                }
            }
        ?>
        <div class="container">
            <?php
                if($aux_feriados!=0){
                    if($status_feriados=="OK"){
                        echo '<div class="clima">
                                <h2>Clima</h2>';
                        echo '<div id=chart_div style=width:600px;height:400px;></div>';
                        echo '<h3>Sugestões: </h3>';
                        if(count($finais_de_semana_sol)>0){
                            echo '<p class=item>Os próximos finais de semana(';
                            foreach($finais_de_semana_sol as $key=>$value){
                                if($key!=0)
                                    echo ' ,';
                                echo "$value";
                            }
                            echo ') estarão ensolarados, prepare-se para aproveitar.</p>';
                        }
                        else
                            echo '<p class=item>Os próximos finais de semana não estarão ensolarados.</p>';
                        echo '</div>';
                    }
                }
            ?>

            <?php
                if($aux_feriados!=0){
                    if($status_feriados=="OK"){
                        echo '<div class="feriados">
                                <h2>Feriados</h2>';
                        foreach($resp_feriados as $key => $value){
                            echo '<p class="text_feriado">';
                            echo "Nome: ".$value->name;
                            echo " - Data: ".$value->date;
                            echo " - Tipo: ".$value->type;
                            echo "</p>";
                        }
                        echo '<h3>Sugestões:</h3>';
                        if(count($feriado_sol)>0){
                            echo "<p class=item>Talvez você possa curtir os feriados ";
                            foreach($feriado_sol as $key=>$value){
                                if($key!=0)
                                    echo ' ,';
                                echo "$value";
                            }
                            echo "em um clube... Os dias estarão ensolarados.</p>";
                        }
                        else{
                            echo "<p class=item>Os feriados deste mês não terão seus dias ensolarados</p>";
                        }
                        echo '</div>';
                    }
                    else{
                        echo '
                        <script>
                            alert("Digite um ano entre 1900 e 2199");
                        </script>
                        ';
                    }
                }
            ?>
        </div>

        <script type="text/javascript">
            var status = "<?php echo "$status_clima"?>";
            console.log(status);
            if(status == "OK"){
                google.charts.load('current', {'packages': ['line']});                
                google.charts.setOnLoadCallback( drawChart );

                function drawChart(){
                    var data = new google.visualization.DataTable();
                    data.addColumn('string', 'Dia');
                    data.addColumn('number', 'Min');
                    data.addColumn('number', 'Max');

                    data.addRows(
                        [
                            <?php
                                foreach($resp_clima->forecast as $key => $value){
                                    echo "[ '$value->date'"." , ".$value->min." , ".$value->max." ],";
                                }
                            ?>
                            //['14/05', 17, 27],
                            //['15/05', 17, 27],
                            //['16/05', 17, 27],
                            //['17/05', 17, 27],
                        ]
                    );

                    var options = {
                        chart: {title: 'Previsão do Tempo'},
                        axes: {
                            x: {label: 'Dia'},
                            y: {label: 'Temperatura(Celsius)'}
                        },
                        backgroundColor: '#FFE4B5',
                    };

                    var chart = new google.charts.Line(document.getElementById('chart_div'));
                    chart.draw(data, google.charts.Line.convertOptions(options));
                }
            }
        </script>
    </body>
</html>