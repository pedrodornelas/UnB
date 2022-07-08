<?php
    $aux_cep = 0;
    $aux_feriados = 0;

    if(isset($_GET['cep'])){
        $aux_cep = 1;
        $cep = $_GET['cep'];
        //echo "$cep<br>";

        $url = "https://brasilapi.com.br/api/cep/v1/$cep";

        $resp_cep = file_get_contents("$url");
        $resp_cep = json_decode($resp_cep);

        if($resp_cep){
            $status_cep="OK";
            //print_r($response);
            $cidade=$resp_cep->city;
            $estado=$resp_cep->state;
            
            //if(isset($_GET['ano'])){
                $aux_feriados=1;
                //$ano = $_GET['ano'];
                $ano = 2021;
                //echo "$ano<br>";
        
                $token = "cGhkb3JuZWxhcy5hbG1laWRhQGdtYWlsLmNvbSZoYXNoPTE2Njk4Mjk3NA";
                $url = "https://api.calendario.com.br/?json=true&ano=$ano&estado=$estado&cidade=$cidade&token=$token";
                //$url = "https://brasilapi.com.br/api/feriados/v1/$ano";

                $resp_feriados = file_get_contents("$url");
                $resp_feriados = json_decode($resp_feriados);
        
                if($resp_feriados){
                    $status_feriados="OK";
                    //print_r($resp_feriados);

                    //Consulta clima
                    $aux_clima=1;
                    $city_name = "$cidade,$estado";
                    $city_name = urlencode($city_name);
                    
                    //$key="0";
                    $key = "779dc0db";
                    $url = "https://api.hgbrasil.com/weather?fields=only_results,forecast,condition,humidity,city_name,date,description,weekday,temp,min,max&city_name=$city_name&key=$key";

                    $resp_clima = file_get_contents("$url");
                    $resp_clima = json_decode($resp_clima);

                    if($resp_clima){
                        $status_clima="OK";
                        //print_r($resp_clima);

                        $finais_de_semana_sol = array();
                        $feriado_sol = array();
                        $dias_sol = array();

                        //$resp_clima->

                        foreach($resp_clima->forecast as $key => $value){
                            if(($value->weekday == "Sáb" || $value->weekday == "Dom") && ($value->description == "Tempo nublado" || $value->description == "Ensolarado"))
                                $finais_de_semana_sol[]=$value->date;

                            foreach($resp_feriados as $chave => $valor){
                                $feriado = $valor->date;
                                if(($feriado == $value->date) && ($value->description == "Tempo nublado" || $value->description == "Ensolarado"))
                                    $feriado_sol[]=$feriado;
                            }
                        }
                        //print_r($finais_de_semana_sol);
                        //print_r($feriado_sol);
                        
                    }
                    else
                        $status_clima="ERROR";
                }
                else{
                    $status_feriados="ERROR";
                }
            //}
            //else
                //$aux_feriados = 0;
    
        }
        else{
            $status_cep="ERROR";
        }

    }
    else
        $aux_cep = 0;
    //header("Location: index.php?aux=$aux");

?>