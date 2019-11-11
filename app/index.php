<?php
/****************************************************
 /  Autor:   edsonns@gmail.com                      
 /  Data:    10/11/2019 07:42h                      
 /  Cliente: CERTI.ORG.BR  
 /  Projeto: Processo de Desenvolvedor                          
 /***************************************************/
 // Arquivo principal

 
//--------------------------------------------------

include("respostas_http.inc");
include("logica.inc");
 
//--------------------------------------------------
//               MAIN
//--------------------------------------------------


$debugAtivado = verificaComandoAtivarDebug($_SERVER['QUERY_STRING']);

$idioma = detectaIdioma($_SERVER['HTTP_ACCEPT_LANGUAGE']);
carregaIdioma($idioma);
debug("idioma dectado=" . $idioma);

$numeroSolicitado = detectaNumero($_SERVER['PATH_INFO']);
debug("numero dectado=" . $numeroSolicitado);

$DigitosPorExtenso = CoverteDigitosEmExtenso($numeroSolicitado);
debug("DigitosPorExtenso=" . $DigitosPorExtenso);

wb_responseWitchOneRecord(EXTENSO,$DigitosPorExtenso);

//--------------------------------------------------




?>
