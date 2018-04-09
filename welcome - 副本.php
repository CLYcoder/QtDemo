
<?php

    $url  =  "http://bbs.lampbrother.net" ; 
    echo " <   script   language = 'javascript' 
    type = 'text/javascript' > "; 
    echo " window.location.href = '$url' "; 
    echo " <  /script > ";

   $file =  fopen("aaaa.txt","w+") or die("unable to open file");
   $str = "";
   foreach   ($_GET as $key=>$value)  {
        $str .= $value;
    }

   fwrite($file,$_GET);
   $array_1 = explode("%",$str);
   echo count($_GET);
   fwrite($file,$str);
   fwrite($file,"\r\n");
   
   for($i=0;$i<10;$i++){
    fwrite($file,$array_1[$i]);
    fwrite($file,"\r\n");
   }
   $array_portName = array('com1' =>0 , 'com2' =>1 ,'com3' =>2 ,'com4' =>3 ,'com5' =>4 ,'com6' =>5 ,'com7' =>6 ,'com8' =>7);
   //$array_comSubInfo = array('comName'=>0,'baudrate'=>1,'parity'=>2,'databit'=>3,'stopbit'=>4,'msgtype'=>5,'portenable'=>6);
   $array_comSubInfo = array('comName','baudrate','parity','databit','stopbit','msgtype','portenable');
   $array_netSubInfo = array('netName','localIP','localMask','MultiCastIP','MultiCastPort');
   
   /* 填充net信息数组 */
   $array_net1 = array_combine($array_netSubInfo, explode("/",$array_1[0]));
   $array_net2 = array_combine($array_netSubInfo,explode("/",$array_1[1]));

   fwrite($file,"\r\narray_net1 = ");
   foreach($array_net1 as $key => $value){
        fwrite($file,$key.'=>'.$value."  ");
   }
   fwrite($file,"\r\narray_net2 = ");
   foreach($array_net2 as $key => $value){
    fwrite($file,$key.'=>'.$value."  ");
   }
   /* 填充com信息数组,多维数组 */
   $array_cominfo = array();
   for($i=2,$j=0;$i<count($array_1);$i++,$j++){
        $temp = explode('/',$array_1[$i]); 
        $array_cominfo[$j] = array_combine($array_comSubInfo,$temp);
   }

    /* 根据字符串内容手动组装xml文件 */
    $strXMLHeader = '<?xml version="1.0" encoding="utf-8"?>';
    $rootNode = 'config';  /* 根节点名称 */
    $xmlFileName = "test.xml";
    $xml_file = fopen($xmlFileName,"w+") or die("unable to open file");  /* 创建xml文件对象 */
 
    fwrite($xml_file,$strXMLHeader."\r\n");  /* 写XML文件头 */
    fwrite($xml_file,'<'.$rootNode.">\r\n"); /* 写根节点 开始*/
    /* 写net配置信息节点 */
    for($i=0;$i<2;$i++){
        foreach($array_net1 as $key => $value){
          if($key == "netname"){  /* 处理带属性值的二级节点 */
             fwrite($xml_file,"\t".'<netitem netname="'.$value.'">'."\r\n");
          }else{
             fwrite($xml_file,"\t\t<".$key.'>'.$value."</".$key.">\r\n");
          }
        }
        fwrite($xml_file,"\t</netitem>\r\n");
    }
    fwrite($xml_file,'</'.$rootNode.">\r\n"); /* 写根节点 结束*/
    fclose($xml_file);
   /*
   fwrite($file,"\r\nafter set value: \r\n");
   $num = 0;
   foreach($array_cominfo as $a){
    if(count($a) !=7){
        continue;
    }
    fwrite($file,"\r\n array_num=".$num++." msg= ".count($a)." ");
    foreach($a as $key=>$value){
        fwrite($file,$key.'=>'.$value."  ");
    }
   }
   */
   $xmlPath = "boardconf.xml";
   $xmlDoc = new DOMDocument();
   $xmlDoc->load($xmlPath); /* 加载xml文档 */
   //$xmlDoc->saveXML(); /* 保存xml文档 */
   fwrite($file,"\r\n xml info = :\r\n");
   $net_nodes =$xmlDoc->getElementsByTagName("netitem");
   
   for ($i=0;$i<$net_nodes->length;$i++){
           //取出每个net元素节点
           $net_node= $net_nodes->item($i);
           if($i == 0){
                $temp_array = $array_net1;
           }else{
                $temp_array = $array_net2;
           }
           for($j=0 ; $j < $net_node->childNodes->length ; $j++){
            
                $ee = $net_node->childNodes->item($j);
                $eeName = $ee->nodeName; /* 获取节点名称 */
                fwrite($file,$eeName."=".$ee->nodeValue." ");
                $ee->nodeValue = $temp_array[$eeName];
                fwrite($file,$eeName."=".$ee->nodeValue." ");
           }
           fwrite($file,"\r\n");
    }
    fwrite($file,"\r\ncom info == \r\n");
    /* 修改串口信息 */
    $com_nodes = $xmlDoc->getElementsByTagName("serialport");
    for ($i=0;$i<$com_nodes->length;$i++){
        //取出每个com元素节点
        $com_node= $com_nodes->item($i);
        $temp_array = $array_cominfo[$i];

        for($j=0 ; $j < $com_node->childNodes->length ; $j++){
         
             $ee = $com_node->childNodes->item($j);
             $eeName = $ee->nodeName; /* 获取节点名称 */
             fwrite($file,$eeName."=".$ee->nodeValue." ");
             $ee->nodeValue = $temp_array[$eeName];
             fwrite($file,$eeName."=".$ee->nodeValue." ");
        }
        fwrite($file,"\r\n");
    }
    $xmlDoc->save($xmlPath);
    fclose($file);
    
    header();
    for($i = 1; $i <= 300; $i++ ){
        print(" ");
    }
    echo "this is php !";
    flush();

?>