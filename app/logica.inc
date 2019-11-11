<?php
/****************************************************
 /  Autor:   edsonns@gmail.com                      
 /  Data:    10/11/2019 07:42h                      
 /  Cliente: CERTI.ORG.BR  
 /  Projeto: Processo de Desenvolvedor                          
 /***************************************************/
 // Arquivo logica


define("_CEM",                           "cem"); 
define("_ZERO",                          "zero");  
define("_MIL",                           "mil"); 
define("_100",                           "100"); 
define("_000",                           "000"); 
define("_0",                             "0"); 
define("QTDE_DIGITOS_ENTRADA",           6);
define("LIMITE_INFERIOR_ENTRADA",        -99999);
define("LIMITE_SUPERIOR_ENTRADA",        99999);
define("SIGLA_IDIOMA_ENGLISH",           "en");
define("SIGLA_IDIOMA_FRENCH",            "fr");
define("SIGLA_IDIOMA_SPANISH",           "es");
define("SIGLA_IDIOMA_PORTUGUESE",        "pt");
define("SIGLA_IDIOMA_DEFAULT",           "pt");
define("NOME_ARQUIVO_IDIOMA",            "_dados.inc");
define("CARACTER_SEPARADOR_MDCU",        " e ");
define("CARACTER_UNIAO_D_U",             "Caracter Uniao Dezenas");
define("PRONUNCIA_MENOS",                "menos");
define("CARACTER_MENOS",                 "-");
define("QUERY_STRING_DEBUG_ON",          "DEBUG");
define("CARACTER_FORCE_DEBUG",           "-f");
define("PRONUNCIA_ERRO_01",              "ERRO_01");
define("PRONUNCIA_ERRO_02",              "ERRO_02");
define("EXTENSO",                        "extenso");
define("FLAG_OMISSAO_UNIDADE_DE_MILHAR", "001");

$numerosExtenso_0a19=NULL;
$numerosExtenso_dezenas=NULL;
$numerosExtenso_centenas=NULL;
$verbete=NULL;
 
 
//--------------------------------------------------
//          REFERENTE AO IDIOMA    
//--------------------------------------------------

function detectaIdioma($idiomaFornecido){
	
	//idiomaFornecido pode assumir:
	//Accept-Language: fr-CH, fr;q=0.9, en;q=0.8, de;q=0.7, *;q=0.5
	//Accept-Language: en-US,en;q=0.5
		
	if (is_null ($idiomaFornecido)){
		return SIGLA_IDIOMA_DEFAULT;
	}
	debug("idiomaFornecido=".$idiomaFornecido);
	$siglaIdioma = substr($idiomaFornecido,0,2); 
	
	debug("siglaIdioma=".$siglaIdioma);
	
	switch ($siglaIdioma) {
		case SIGLA_IDIOMA_ENGLISH:
		case SIGLA_IDIOMA_FRENCH:
		case SIGLA_IDIOMA_SPANISH:
		case SIGLA_IDIOMA_PORTUGUESE:

			break;
		default:
			$siglaIdioma = SIGLA_IDIOMA_DEFAULT;
	}	
	
	debug("siglaIdiomaDetectada=".$siglaIdioma);
	return $siglaIdioma;
}

//--------------------------------------------------

function carregaIdioma($idiomaDetectado){
	try {
		$arquivoIdioma = $idiomaDetectado . NOME_ARQUIVO_IDIOMA;
		include("idiomas/". $arquivoIdioma);
		$GLOBALS["numerosExtenso_0a19"]=$numerosExtenso_0a19;
		$GLOBALS["numerosExtenso_dezenas"]=$numerosExtenso_dezenas;
		$GLOBALS["numerosExtenso_centenas"]=$numerosExtenso_centenas;
		$GLOBALS["verbete"]=$verbete;	
	} catch  (Exception $e) {		
		responde500($e->getMessage());
		debug($e->getMessage());
		die();
    }
}


//--------------------------------------------------
//          REFERENTE AO NÚMERO   
//--------------------------------------------------


function detectaNumero($numeroFornecido){
	/*
	numeroFornecido pode assumir:
	/-99999 a /99999
	/1
	/0
	/94587
	*/	
	
	try {
		$numero = substr($numeroFornecido,1); //remove uma barra
		
		if (!(is_numeric($numero))){
			throw new Exception(PRONUNCIA_ERRO_02); //Valor informado não é numérico
		}
		$numeroINT = intval($numero);
		if (($numeroINT<LIMITE_INFERIOR_ENTRADA) or ($numeroINT>LIMITE_SUPERIOR_ENTRADA)){
			throw new Exception(PRONUNCIA_ERRO_01); //Valor fora do intervalo
		}
		$numeroSTR = strval($numero);
		$possivelSinalDeMenos = substr($numeroSTR,0,1); //obtem primeiro caracter
		if ($possivelSinalDeMenos == CARACTER_MENOS ) {
			$numeroSTR = substr($numeroSTR,1); //retira o caracter menos
		}	
		$numeroSTR = str_pad($numeroSTR, QTDE_DIGITOS_ENTRADA, _0, STR_PAD_LEFT); //Coloca zeros à esquerda para ficar com 6 dígitos
		if ($possivelSinalDeMenos == CARACTER_MENOS ) {
			$numeroSTR = CARACTER_MENOS . $numeroSTR; //devolve o sinal menos
		}
		
		return $numeroSTR;
	} catch (Exception $e){
		$verbete=$GLOBALS["verbete"];
		$msgErro = $verbete[$e->getMessage()]; 
		debug("msgErro".$msgErro);
		responde405($msgErro);
		debug("msgErro".$msgErro);
		die();
	}
}

//--------------------------------------------------

function CoverteTresDigitosEmExtenso($CDU){
	
	
	$numerosExtenso_0a19=$GLOBALS["numerosExtenso_0a19"];
	$numerosExtenso_dezenas=$GLOBALS["numerosExtenso_dezenas"];
	$numerosExtenso_centenas=$GLOBALS["numerosExtenso_centenas"];
	$verbete=$GLOBALS["verbete"];	
	$caracterSeparador = $verbete[CARACTER_SEPARADOR_MDCU];
	$caracterUniaoD_U =  $verbete[CARACTER_UNIAO_D_U];
	
	
	$valorPorExtenso="";
	
	if ($CDU == _100) { 
		$valorPorExtenso = $verbete[_CEM]; //=cem ou conforme o idioma solicitado
		return $valorPorExtenso;
	};
	if ($CDU == _000) { 
		$valorPorExtenso = $verbete[_ZERO]; //=zero ou conforme o idioma solicitado		
		return $valorPorExtenso;
	};
	//CDU ainda pode ser 101.... ou 099...
	$digitoC = $CDU[0];
	$digitoCentenaPorExtenso = $numerosExtenso_centenas[$digitoC]; //pode ser vazio ou centena por extenso conforme o idioma solicitado	
	debug("digitoCentenaPorExtenso = >".$digitoCentenaPorExtenso."<");
	$digitosDU = $CDU[1] . $CDU[2];
	
	if (array_key_exists($digitosDU, $numerosExtenso_0a19)) { //Se os digitos DU estão entre 0 a 19
			
		$valorDe0a19PorExtenso = $numerosExtenso_0a19[$digitosDU]; //por extenso conforme o idioma solicitado		
		if ($digitoCentenaPorExtenso != "" ){ 	//ou seja, um valor maior que 99 
			$valorPorExtenso = $digitoCentenaPorExtenso . $caracterSeparador . $valorDe0a19PorExtenso;
		} else {
			$valorPorExtenso = $valorDe0a19PorExtenso;
		}
		return $valorPorExtenso;
	}
	
	$digitosD = $CDU[1];
	$digitoDezenaPorExtenso = $numerosExtenso_dezenas[$digitosD];
    debug("numerosExtenso_dezenas[".$digitosD."] = >".$digitoDezenaPorExtenso."<");
	
	if ($digitoCentenaPorExtenso != "" ){ 	//ou seja, um valor maior que 99 
		$valorPorExtenso = $digitoCentenaPorExtenso . $caracterSeparador . $digitoDezenaPorExtenso;
	}else {
		$valorPorExtenso = $digitoDezenaPorExtenso;
	}
	
	$digitosU = $CDU[2];
	if ($digitosU!=_0){
		
		if ($caracterUniaoD_U!="") {
			$valorPorExtenso =  $valorPorExtenso . $caracterUniaoD_U . $numerosExtenso_0a19[_0.$digitosU];
		} else {
			$valorPorExtenso =  $valorPorExtenso . $caracterSeparador . $numerosExtenso_0a19[_0.$digitosU];
		}
	}
	return $valorPorExtenso;
	
	
}

//--------------------------------------------------

function CoverteDigitosEmExtenso($CDUcdu){
	
	
	$possivelSinalDeMenos = substr($CDUcdu,0,1); //obtem primeiro caracter
    if ($possivelSinalDeMenos == CARACTER_MENOS ) {
		$CDUcdu = substr($CDUcdu,1); //retira o caracter menos
	}	
	
	$verbete=$GLOBALS["verbete"];	
	$pronunciaMenos =  $verbete[PRONUNCIA_MENOS];
	$caracterSeparador = $verbete[CARACTER_SEPARADOR_MDCU];	
	
	$valorPorExtenso = "";
	$cdu = $CDUcdu[3] . $CDUcdu[4] . $CDUcdu[5];
	$cduPorExtenso = CoverteTresDigitosEmExtenso($cdu);

	$CDU = $CDUcdu[0] . $CDUcdu[1] . $CDUcdu[2];
	$CDUPorExtenso = CoverteTresDigitosEmExtenso($CDU);
	
	if ($CDUPorExtenso != $verbete[_ZERO] ){
		if (($GLOBALS["idioma"] == SIGLA_IDIOMA_PORTUGUESE) AND (FLAG_OMISSAO_UNIDADE_DE_MILHAR==$CDU)){
			$valorPorExtenso = $verbete[_MIL] . $caracterSeparador .  $cduPorExtenso;
		}else {
			$valorPorExtenso = $CDUPorExtenso . " " .$verbete[_MIL] . $caracterSeparador .  $cduPorExtenso;	
		}
	} else {
		$valorPorExtenso = $cduPorExtenso;
	}

    if ($possivelSinalDeMenos == CARACTER_MENOS ) {
		$CDUcdu = CARACTER_MENOS . $CDUcdu; //devolve  sinal menos
		$valorPorExtenso = $pronunciaMenos . $valorPorExtenso;
	}
	
	
	debug("CDU = "    . $CDU    . " = " . $CDUPorExtenso  );
	debug("cdu = "    . $cdu    . " = " . $cduPorExtenso  );
	debug("CDUcdu = " . $CDUcdu . " = " . $valorPorExtenso);	
	return $valorPorExtenso;
}


//--------------------------------------------------
//          REFERENTE AO DEBUG
//--------------------------------------------------
function verificaComandoAtivarDebug($ComandoAtivarDebug){
	
	$resposta = false;
	
	if (empty($ComandoAtivarDebug)) {
		$resposta = false;
	} else {		
		if ($ComandoAtivarDebug == QUERY_STRING_DEBUG_ON) {
			$resposta = true;
		}
	}	
	return $resposta;
}
	
//--------------------------------------------------

function debug($msg,$force=""){
	if (($force == CARACTER_FORCE_DEBUG) or ($GLOBALS["debugAtivado"])){
		echo "\ndebug:" . $msg . "\n";
	}
}

//--------------------------------------------------




?>
