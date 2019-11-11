<?php
/****************************************************
 /  Autor:   edsonns@gmail.com                      
 /  Data:    10/11/2019 09:45h                      
 /  Cliente: CERTI.ORG.BR  
 /  Projeto: Processo de Desenvolvedor                          
 /***************************************************/
 // Arquivo com respostas HTTP 
 
 
 
  /**
 * **************************************************
 * / RESPOSTAS - JSON /
 * /**************************************************
 */
 
 function wb_responseWitchOneRecord($chave, $valor)
{
    $Dados = "{ \"".$chave."\": \"".$valor."\" }\n";
	if (!($GLOBALS["debugAtivado"])){
		header('Content-Type: application/json');
	}
    responde200();
    echo $Dados;
}
 
 
 /**
 * **************************************************
 * / RESPOSTAS - Headers standard /
 * /**************************************************
 */
function respondeStandard()
{
	if (!($GLOBALS["debugAtivado"])){
		header('Access-Control-Allow-Origin: *');
	}	
}
/**
 * **************************************************
 * / RESPOSTAS - 200 /
 * /**************************************************
 */
function responde200($msg="")
{
    respondeStandard();
	if (!($GLOBALS["debugAtivado"])){
		header("HTTP/1.0 200");
	}	
    echo $msg;
}
 /**
 * **************************************************
 * / RESPOSTAS - 500 /
 * /**************************************************
 */
function responde500($msg)
{
    respondeStandard();
	if (!($GLOBALS["debugAtivado"])){
		header("HTTP/1.0 500");
	}	
    echo "<br>".$msg."\n";
    die();
} 
/**
 * **************************************************
 * / RESPOSTAS - 405 /
 * /**************************************************
 */
function responde405($msg)
{
    respondeStandard();
	if (!($GLOBALS["debugAtivado"])){
		header("HTTP/1.0 405 M�todo n�o permitido");
	}	
    echo "<br>".$msg."\n";
}



?>