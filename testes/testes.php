<?php
/****************************************************
 /  Autor:   edsonns@gmail.com                      
 /  Data:    10/11/2019 07:42h                      
 /  Cliente: CERTI.ORG.BR  
 /  Projeto: Processo de Desenvolvedor                          
 /***************************************************/
 // Arquivo TESTES

include("../app/logica.inc");
include("../app/respostas_http.inc");


$GLOBALS["debugAtivado"]=false;
TesteALL();

//----------------------------------------------------------------
function TesteALL(){	
    $GLOBALS["debugAtivado"]=false;
	Teste_detectaIdioma();	
	$GLOBALS["debugAtivado"]=false;	
	Teste_detectaNumero();
	
}
//----------------------------------------------------------------
function Teste_detectaNumero(){
	
	unset($arrayTestes);	
	$arrayTestes = array (
	array ('testeN'=>1, 'Param'=>'/12345',   'saidaEsperada'=>'012345',  'resultado'=>NULL,'valorRetornado'=>NULL),
	array ('testeN'=>2, 'Param'=>'/-11',      'saidaEsperada'=>'-000011', 'resultado'=>NULL,'valorRetornado'=>NULL), 
	array ('testeN'=>3, 'Param'=>'/123',     'saidaEsperada'=>'000123',  'resultado'=>NULL,'valorRetornado'=>NULL), 
	array ('testeN'=>4, 'Param'=>'/-99123',  'saidaEsperada'=>'-099123', 'resultado'=>NULL,'valorRetornado'=>NULL), 
	array ('testeN'=>5, 'Param'=>'/-123',    'saidaEsperada'=>'-000123', 'resultado'=>NULL,'valorRetornado'=>NULL), 	

	);	 
	 
	foreach ($arrayTestes as &$item) {
	   try{	
		   $item['valorRetornado']	= detectaNumero($item['Param']);
		   debug("\n---------".$item['valorRetornado']);
		   $item['resultado'] = myAssert($item['valorRetornado'], $item['saidaEsperada']);
	   } catch (Exception $e){
		   $item['resultado'] = $e->getMessage();
	   }

	}		
	relatorio(__FUNCTION__,$arrayTestes);
	 
}

//----------------------------------------------------------------
 function Teste_detectaIdioma(){
    $valorDefault = "pt";
	$arrayTestes = array (
	array ('testeN'=>1, 'Param'=>'*',                                             'saidaEsperada'=>$valorDefault, 'resultado'=>NULL,'valorRetornado'=>NULL),
	array ('testeN'=>2, 'Param'=>'fr-CH, fr;q=0.9, en;q=0.8, de;q=0.7, *;q=0.5',  'saidaEsperada'=>'fr',          'resultado'=>NULL,'valorRetornado'=>NULL), 
	array ('testeN'=>3, 'Param'=>'de',                                            'saidaEsperada'=>$valorDefault, 'resultado'=>NULL,'valorRetornado'=>NULL),
	array ('testeN'=>4, 'Param'=>'de-CH',                                         'saidaEsperada'=>$valorDefault, 'resultado'=>NULL,'valorRetornado'=>NULL),
	array ('testeN'=>5, 'Param'=>'en-US,en;q=0.5',                                'saidaEsperada'=>'en',          'resultado'=>NULL,'valorRetornado'=>NULL),  
	array ('testeN'=>6, 'Param'=>'*/*',                                           'saidaEsperada'=>$valorDefault, 'resultado'=>NULL,'valorRetornado'=>NULL)
	);	 
	 
	foreach ($arrayTestes as &$item) {
		
	   $item['valorRetornado']	= detectaIdioma($item['Param']);
	   debug("\n---------".$item['valorRetornado']);
	   $item['resultado'] = myAssert($item['valorRetornado'], $item['saidaEsperada']);

	}		
	relatorio(__FUNCTION__,$arrayTestes);

 }
//----------------------------------------------------------------
 
 function myAssert($valorcalculado, $valorEsperado){
	 $reposta = ($valorcalculado == $valorEsperado);
	 return $reposta;
}
 
//----------------------------------------------------------------
 function relatorio($nomeTeste, $arrayTestes){
	$qdeAcertos=0;
	$qdeErros=0;
	 
	foreach ($arrayTestes as $item) {
	   if($item['resultado']){
		   $qdeAcertos++;
	   }else {
		   $qdeErros++;
		   echo "\ntesteN=".$item['testeN'];
		   echo "\n----Valor esperado:" .$item['saidaEsperada'];
		   echo "\n----Valor retornado:" .$item['valorRetornado'];
	   }		
	}
	echo "\nTeste:". $nomeTeste;
	echo "\nQtde Acertos=".$qdeAcertos;
	echo "\nQtde qdeErros=".$qdeErros;
	echo "\n";
 }
 
?>