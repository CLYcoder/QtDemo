/**
 * 响应查询按钮的点击
 */
function onCheckBtnClicked() {
    xmlDoc = loadXML("boardconf.xml");

    if (xmlDoc == null) {
        console.log("load xml failed");
        return;
    }
    document.getElementById("net1_ip").value = xmlDoc.getElementsByTagName("localIP")[0].childNodes[0].nodeValue;
    document.getElementById("net1_mask").value = xmlDoc.getElementsByTagName("localMask")[0].childNodes[0].nodeValue;
    document.getElementById("net1_destip").value = xmlDoc.getElementsByTagName("MultiCastIP")[0].childNodes[0].nodeValue;
    document.getElementById("net1_destport").value = xmlDoc.getElementsByTagName("MultiCastPort")[0].childNodes[0].nodeValue;

    document.getElementById("net2_ip").value = xmlDoc.getElementsByTagName("localIP")[1].childNodes[0].nodeValue;
    document.getElementById("net2_mask").value = xmlDoc.getElementsByTagName("localMask")[1].childNodes[0].nodeValue;
    document.getElementById("net2_destip").value = xmlDoc.getElementsByTagName("MultiCastIP")[1].childNodes[0].nodeValue;
    document.getElementById("net2_destport").value = xmlDoc.getElementsByTagName("MultiCastPort")[1].childNodes[0].nodeValue;

    /* 设置每一行串口的信息 */
    for (var i = 1; i < 9; i++) {
        setTableLineData(xmlDoc, i);
    }

}
loadXML = function(xmlFile) {
    var xmlDoc = null;
    var agent = navigator.userAgent.toLowerCase();

    //判断浏览器的类型  
    //支持IE浏览器  
    if (agent.indexOf("msie") > 0) {
        //alert("22");
        var xmlDomVersions = ['MSXML.2.DOMDocument.6.0', 'MSXML.2.DOMDocument.3.0', 'Microsoft.XMLDOM'];
        for (var i = 0; i < xmlDomVersions.length; i++) {
            try {
                xmlDoc = new ActiveXObject(xmlDomVersions[i]);
                break;
            } catch (e) {}
        }
    }
    //支持firefox浏览器  
    else if (agent.indexOf("firefox") > 0) {
        try {
            xmlDoc = document.implementation.createDocument('', '', null);
        } catch (e) {}
    } else { //谷歌浏览器  
        //alert("111111111");
        var oXmlHttp = new XMLHttpRequest();
        oXmlHttp.open("GET", xmlFile, false);
        oXmlHttp.send(null);
        return oXmlHttp.responseXML;
    }
    if (xmlDoc != null) {
        xmlDoc.async = false;
        xmlDoc.load(xmlFile);
    }
    return xmlDoc;
}

/**
 * 加载xml文档
 * @param {*} dname 
 */
function loadXMLDoc(xmlFile) {

    if (window.XMLHttpRequest) {
        xhttp = new XMLHttpRequest();
    } else {
        xhttp = new ActiveXObject("Microsoft.XMLHTTP");
    }
    xhttp.open("GET", xmlFile, false);
    xhttp.send();
    return xhttp.responseXML;
}

/**
 * 响应更新配置按钮的点击
 */
function onUpdateBtnClicked() {

    str = capturePageInfos();

    if (window.XMLHttpRequest) {
        // IE7+, Firefox, Chrome, Opera, Safari 浏览器执行的代码
        xmlhttp = new XMLHttpRequest();
    } else {
        //IE6, IE5 浏览器执行的代码
        xmlhttp = new ActiveXObject("Microsoft.XMLHTTP");
    }
    /*
    xmlhttp.onreadystatechange = function() {
        if (xmlhttp.readyState == 4 && xmlhttp.status == 200) {
            document.getElementById("txtHint").innerHTML = xmlhttp.responseText;
        }
    }*/
    xmlhttp.open("GET", "welcome.php?str=" + str, true);
    xmlhttp.send();
    console.log("script worked");

}


/**
 * 根据传递的参数数值
 * @param {*} str 端口号 
 */
function onCheckedChanged(str) {
    var baud_id = str + "_baud";
    var parity_id = str + "_parity";
    var data_id = str + "_databit";
    var stop_id = str + "_stopbit";
    var type_id = str + "_msgtype";
    var checked_id = str + "_checked";
    var line_id = str + "_line";

    var flag = document.getElementById(checked_id).checked;
/*
    if (flag == true) {
        // 设定行元素是否可选以及背景色 
        document.getElementById(baud_id).disabled = false;
        document.getElementById(parity_id).disabled = false;
        document.getElementById(data_id).disabled = false;
        document.getElementById(stop_id).disabled = false;
        document.getElementById(type_id).disabled = false;
        document.getElementById(line_id).setAttribute("isDisable", "1");
        document.getElementById(line_id).attributes['isDisable'].nodeValue = '1';
    } else {
        document.getElementById(baud_id).disabled = true;
        document.getElementById(parity_id).disabled = true;
        document.getElementById(data_id).disabled = true;
        document.getElementById(stop_id).disabled = true;
        document.getElementById(type_id).disabled = true;
        document.getElementById(line_id).setAttribute("isDisable", "1");
        document.getElementById(line_id).attributes['isDisable'].nodeValue = '0';
    }
    */
}

/**
 * 设置select标签显示的内容
 * selectItem 多选框标签对象
 * str 多选框匹配项
 */
function setSelectOption(selectItem, str) {
    console.log(selectItem.id + "  " + str);
    var i = 0;
    var flag = true;
    /* 遍历options列表 */
    for (i = 0; i < selectItem.options.length; i++) {
        if (selectItem.options[i].value == str) {
            selectItem.selectedIndex = i;
            flag = false;
            console.log("find " + str + " in " + i + "th in select[" + selectItem.id + "]");
        }
    }
    if (flag) {
        console.log("select[" + selectItem.id + "]  can't find " + str);
    }
}

/**
 * 设置一行列表的数据内容 
 * @param {*} num 串口编号
 * xmlDoc xml解释器对象
 */
function setTableLineData(xmlDoc, num) {
    var str = "com" + num;
    var baud_id = str + "_baud";
    var parity_id = str + "_parity";
    var data_id = str + "_databit";
    var stop_id = str + "_stopbit";
    var type_id = str + "_msgtype";
    var checked_id = str + "_checked";

    setSelectOption(document.getElementById(baud_id), xmlDoc.getElementsByTagName("baudrate")[num - 1].childNodes[0].nodeValue);
    setSelectOption(document.getElementById(parity_id), xmlDoc.getElementsByTagName("parity")[num - 1].childNodes[0].nodeValue);
    setSelectOption(document.getElementById(data_id), xmlDoc.getElementsByTagName("databit")[num - 1].childNodes[0].nodeValue);
    setSelectOption(document.getElementById(stop_id), xmlDoc.getElementsByTagName("stopbit")[num - 1].childNodes[0].nodeValue);

    document.getElementById(type_id).value = xmlDoc.getElementsByTagName("msgtype")[num - 1].childNodes[0].nodeValue;
    var txt = xmlDoc.getElementsByTagName("portenable")[num - 1].childNodes[0].nodeValue;
    var flag = txt == "true" ? true : false;
    console.log("txt=" + txt + "  falg type=" + typeof(flag) + " value=" + flag);

    var check_value = document.getElementById(checked_id).checked;

    if (flag != check_value) {
        document.getElementById(checked_id).click(); /* 模拟一次点击 */
    }
}

/** 
 * 捕获配置界面上当前显示的信息 
 */
function capturePageInfos() {
    /* 捕获网口信息 */
    var i = 0;
    var temp = "eth0/";
    temp += (document.getElementById("net1_ip").value + "/");
    temp += (document.getElementById("net1_mask").value + "/");
    temp += (document.getElementById("net1_destip").value + "/");
    temp += (document.getElementById("net1_destport").value + "%");
    temp += "eth1/";
    temp += (document.getElementById("net2_ip").value + "/");
    temp += (document.getElementById("net2_mask").value + "/");
    temp += (document.getElementById("net2_destip").value + "/");
    temp += (document.getElementById("net2_destport").value + "%");



    for (i = 1; i < 9; i++) {
        temp += captureLineInfo(i);
    }

    console.log(temp);

    return temp;
}

/**
 * 获取列表中某一行的所有信息
 * @param {获取信息的行号} num 
 * @return 拼接玩成的信息 
 */
function captureLineInfo(num) {

    var str = "com" + num;
    var baud_id = str + "_baud";
    var parity_id = str + "_parity";
    var data_id = str + "_databit";
    var stop_id = str + "_stopbit";
    var type_id = str + "_msgtype";
    var checked_id = str + "_checked";
    var temp = str + "/";
    var obj;
    var text;
    obj = document.getElementById(baud_id);
    text = obj.options[obj.selectedIndex].value;
    temp += (text + "/");
    obj = document.getElementById(parity_id);
    text = obj.options[obj.selectedIndex].value;
    temp += (text + "/");
    obj = document.getElementById(data_id);
    text = obj.options[obj.selectedIndex].value;
    temp += (text + "/");
    obj = document.getElementById(stop_id);
    text = obj.options[obj.selectedIndex].value;
    temp += (text + "/");

    temp += (document.getElementById(type_id).value + "/");
    temp += (document.getElementById(checked_id).checked + "%");
    return temp;
}