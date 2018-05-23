<?php

session_start();
//session_destroy();
function redirect($lien){
    header("Location: ".$lien);
}

if(filter_input(INPUT_POST, "chooseType", FILTER_SANITIZE_SPECIAL_CHARS)){
    $_SESSION["chosenType"] = filter_input(INPUT_POST, "typePicker", FILTER_SANITIZE_SPECIAL_CHARS);
    echo $_SESSION["chosenType"];
    redirect("../index.php");
}

if(!isset($_SESSION["chosenType"]) || !isset($_SESSION["allElements"]) || !isset($_SESSION["polyName"]) || !isset($_SESSION["allMateriaux"]) || !isset($_SESSION["shownScene"])){
    $_SESSION["chosenType"] = "Lampe";
    $_SESSION["allElements"] = array();
    $_SESSION["polyName"] = array();
    $_SESSION["allMateriaux"] = array();
    $_SESSION["shownScene"] = "test.jpg";
}

if(filter_input(INPUT_POST, "addSpheroide", FILTER_SANITIZE_SPECIAL_CHARS)){
    $A = filter_input(INPUT_POST, "A", FILTER_SANITIZE_SPECIAL_CHARS);
    $B = filter_input(INPUT_POST, "B", FILTER_SANITIZE_SPECIAL_CHARS);
    $C = filter_input(INPUT_POST, "C", FILTER_SANITIZE_SPECIAL_CHARS);
    $Cx = filter_input(INPUT_POST, "Cx", FILTER_SANITIZE_SPECIAL_CHARS);
    $Cy = filter_input(INPUT_POST, "Cy", FILTER_SANITIZE_SPECIAL_CHARS);
    $Cz = filter_input(INPUT_POST, "Cz", FILTER_SANITIZE_SPECIAL_CHARS);
    $materialName = filter_input(INPUT_POST, "materiaux", FILTER_SANITIZE_SPECIAL_CHARS);
    if($A && $B && $C && $Cx!= NULL && $Cy!= NULL && $Cz!= NULL && $materialName != NULL){
        $newQuadra = array();
        //SP A B C Cx Cy Cz
        array_push($newQuadra, "SP");
        array_push($newQuadra, $A);
        array_push($newQuadra, $B);
        array_push($newQuadra, $C);
        array_push($newQuadra, $Cx);
        array_push($newQuadra, $Cy);
        array_push($newQuadra, $Cz);
        array_push($newQuadra, $materialName);
        array_push(($_SESSION["allElements"]), $newQuadra);
    }
   redirect("../index.php");
}

if(filter_input(INPUT_POST, "setSommets", FILTER_SANITIZE_SPECIAL_CHARS)){
    $nbSommets = filter_input(INPUT_POST, "nbSommets", FILTER_SANITIZE_SPECIAL_CHARS);
    if($nbSommets >= 3){
        $_SESSION["nbSommets"] = $nbSommets;
    }
    else{
        $_SESSION["nbSommets"] = 3;
    }

    redirect("../index.php");
}

if(filter_input(INPUT_POST, "addpoly", FILTER_SANITIZE_SPECIAL_CHARS)){

    $required = array('x', 'y', 'z');
    $ok = true;
    //check if all form's field are filled
    for($i = 1; $i<=$_SESSION["nbSommets"]; $i++){
        foreach($required as $test){
            if(NULL == filter_input(INPUT_POST, $i.$test, FILTER_SANITIZE_SPECIAL_CHARS)){
                $ok = false;
            }
        }
    }
    $nom = filter_input(INPUT_POST, "nom", FILTER_SANITIZE_SPECIAL_CHARS);
    if($ok == true && $nom && !in_array($nom, $_SESSION["polyName"])){
        $newPoly = array();
        array_push($newPoly, "POLY");
        array_push($newPoly, $nom);
        array_push($_SESSION["polyName"], $nom);
        
        //POLY nbPoint pt1x pt1y pt1z pt2x pt2y pt2z...
        array_push($newPoly, $_SESSION["nbSommets"]);
        for($i = 1; $i<=$_SESSION["nbSommets"]; $i++){
            $x = filter_input(INPUT_POST, $i."x", FILTER_SANITIZE_SPECIAL_CHARS);
            $y = filter_input(INPUT_POST, $i."y", FILTER_SANITIZE_SPECIAL_CHARS);
            $z = filter_input(INPUT_POST, $i."z", FILTER_SANITIZE_SPECIAL_CHARS);
            array_push($newPoly, $x);
            array_push($newPoly, $y);
            array_push($newPoly, $z);
        }
        array_push($_SESSION["allElements"], $newPoly);
        $_SESSION["nbSommets"] = NULL;
    }
    
    redirect("../index.php");
}

if(filter_input(INPUT_POST, "addLampe", FILTER_SANITIZE_SPECIAL_CHARS)){
    $newLampe = array();
    array_push($newLampe, "LAMPE");
    //LAMPE X Y Z
    $x = filter_input(INPUT_POST, "X", FILTER_SANITIZE_SPECIAL_CHARS);
    $y = filter_input(INPUT_POST, "Y", FILTER_SANITIZE_SPECIAL_CHARS);
    $z = filter_input(INPUT_POST, "Z", FILTER_SANITIZE_SPECIAL_CHARS);
    $r = filter_input(INPUT_POST, "R", FILTER_SANITIZE_SPECIAL_CHARS);
    $g = filter_input(INPUT_POST, "G", FILTER_SANITIZE_SPECIAL_CHARS);
    $b = filter_input(INPUT_POST, "B", FILTER_SANITIZE_SPECIAL_CHARS);

    if($x!= NULL && $y!= NULL && $z!= NULL && $r!= NULL && $g!= NULL && $b!= NULL){
        array_push($newLampe, $x);
        array_push($newLampe, $y);
        array_push($newLampe, $z);
        array_push($newLampe, $r);
        array_push($newLampe, $g);
        array_push($newLampe, $b);
        array_push($_SESSION["allElements"], $newLampe);
    }

   redirect("../index.php");
}

if(filter_input(INPUT_POST, "addPlan",FILTER_SANITIZE_SPECIAL_CHARS)){
    $a = filter_input(INPUT_POST, "A",FILTER_SANITIZE_SPECIAL_CHARS);
    $b = filter_input(INPUT_POST, "B",FILTER_SANITIZE_SPECIAL_CHARS);
    $c = filter_input(INPUT_POST, "C",FILTER_SANITIZE_SPECIAL_CHARS);
    $d = filter_input(INPUT_POST, "D",FILTER_SANITIZE_SPECIAL_CHARS);
    $materialName = filter_input(INPUT_POST, "materiaux", FILTER_SANITIZE_SPECIAL_CHARS);
    if($a!= NULL && $b!= NULL && $c!= NULL && $d!= NULL && $materialName != NULL){
        //PLAN A B C D
        $plan = array();
        array_push($plan, "PLAN");
        array_push($plan, $a);
        array_push($plan, $b);
        array_push($plan, $c);
        array_push($plan, $d);
        array_push($plan, $materialName);
        array_push($_SESSION["allElements"], $plan);
    }
    redirect("../index.php");
}

if(filter_input(INPUT_POST, "setFaces", FILTER_SANITIZE_SPECIAL_CHARS)){
    $nbFaces = filter_input(INPUT_POST, "nbFaces", FILTER_SANITIZE_SPECIAL_CHARS);
    if($nbFaces >= 3){
        $_SESSION["nbFaces"] = $nbFaces;
    }
    else{
        $_SESSION["nbFaces"] = 3;
    }

    redirect("../index.php");
}

if(filter_input(INPUT_POST, "setSolide", FILTER_SANITIZE_SPECIAL_CHARS)){
    $ok = true;
    $materialName = filter_input(INPUT_POST, "materiaux", FILTER_SANITIZE_SPECIAL_CHARS);
    for($i = 1; $i<=$_SESSION["nbFaces"]; $i++){
        if(NULL == filter_input(INPUT_POST, "poly".$i, FILTER_SANITIZE_SPECIAL_CHARS)){
            $ok = false;
        }
    }


    if($ok == true && $materialName != NULL){
        $solide = array();
        array_push($solide, "SO");
        array_push($solide, $_SESSION["nbFaces"]);
        for($i = 1; $i<=$_SESSION["nbFaces"]; $i++){
           foreach($_SESSION["allElements"] as $current){
                if($current[0] == "POLY" && $current[1] == filter_input(INPUT_POST, "poly".$i, FILTER_SANITIZE_SPECIAL_CHARS)){
                    array_push($solide, $current);
                }
            } 
        }
        array_push($solide, $materialName);
        array_push($_SESSION["allElements"], $solide);
        $_SESSION["nbFaces"] = NULL;
    }
    redirect("../index.php");
}

if(filter_input(INPUT_POST, "execute", FILTER_SANITIZE_SPECIAL_CHARS)){
    $_SESSION["shownScene"] = "test.jpg";
    //unlink("../allInfos");
    $j = 0;
    $string = NULL;
    $fichier = fopen("../allInfos","w");
    fseek($fichier, 0);
    foreach($_SESSION["allElements"] as $current){
        if($current[0] == "SP"){
            $string = $current[0]."\n".$current[1]."\n".$current[2]."\n".$current[3]."\n".$current[4]."\n".$current[5]."\n".$current[6];
            foreach($_SESSION["allMateriaux"] as $mat){
                if($mat[1] == $current[7]){
                    $string = $string."\n".$mat[2]."\n".$mat[3]."\n".$mat[4]."\n".$mat[5]."\n".$mat[6]."\n".$mat[7];
                }
            }
        }
        else if($current[0] == "POLY"){
            $string = $current[0]."\n".$current[1]."\n".$current[2];
            for($i = 1; $i <= $current[2]; $i++){
                $string = $string."\n".$current[$i*3]."\n".$current[3*$i+1]."\n".$current[3*$i+2];

            }
        }
        else if($current[0] == "LAMPE"){
            $string = $current[0]."\n".$current[1]."\n".$current[2]."\n".$current[3]."\n".$current[4]."\n".$current[5]."\n".$current[6];
        }
        else if($current[0] == "PLAN"){
            $string = $current[0]."\n".$current[1]."\n".$current[2]."\n".$current[3]."\n".$current[4];
            foreach($_SESSION["allMateriaux"] as $mat){
                if($mat[1] == $current[5]){
                    $string = $string."\n".$mat[2]."\n".$mat[3]."\n".$mat[4]."\n".$mat[5]."\n".$mat[6]."\n".$mat[7];
                }
            }
            
        }
        else if($current[0] == "SO"){
            var_dump($current);
            $string = $current[0]."\n".$current[1];
            var_dump($current);
            for($i = 0; $i < $current[1]; $i++){
                for($j = 0; $j <= $current[$i+2][2]*3; $j++){
                    $string = $string."\n".$current[$i+2][$j+2];
                }
            }
            foreach($_SESSION["allMateriaux"] as $mat){
                if($mat[1] == $current[$current[1]+2]){
                    $string = $string."\n".$mat[2]."\n".$mat[3]."\n".$mat[4]."\n".$mat[5]."\n".$mat[6]."\n".$mat[7];
                }
            }

        }
        
        if($j == 0){
            var_dump($string);
            fprintf($fichier, "%s",$string);
        }
        else{
            fprintf($fichier, "\r\n%s",$string);
        }
        $j++;
        
    }
    fclose($fichier);
    
    shell_exec(" gcc ../C/test.c ../C/geometric3DTools.c ../C/object.c ../C/bmp.c -lm");
    shell_exec("./a.out");
    redirect("../index.php");
}

if(filter_input(INPUT_POST, "restart", FILTER_SANITIZE_SPECIAL_CHARS)){
    session_destroy();
    redirect("../index.php");
}

if(filter_input(INPUT_POST, "addMateriaux", FILTER_SANITIZE_SPECIAL_CHARS)){
    $nom = filter_input(INPUT_POST, "nom", FILTER_SANITIZE_SPECIAL_CHARS);
    $rouge = filter_input(INPUT_POST, "R", FILTER_SANITIZE_SPECIAL_CHARS);
    $vert = filter_input(INPUT_POST, "V", FILTER_SANITIZE_SPECIAL_CHARS);
    $bleu = filter_input(INPUT_POST, "B", FILTER_SANITIZE_SPECIAL_CHARS);
    $reflexion = filter_input(INPUT_POST, "Reflexion", FILTER_SANITIZE_SPECIAL_CHARS);
    $transparance = filter_input(INPUT_POST, "Transparance", FILTER_SANITIZE_SPECIAL_CHARS); 
    $refraction = filter_input(INPUT_POST, "Refraction", FILTER_SANITIZE_SPECIAL_CHARS);

    if($nom!=NULL && $rouge!=NULL && $vert!=NULL && $bleu!=NULL && $transparance!=NULL && $reflexion!=NULL && $refraction!=NULL && !in_array($nom, $_SESSION["materiauxName"])){
        $newMaterial = array();
        array_push($newMaterial, "MAT");
        array_push($newMaterial, $nom);
        array_push($newMaterial, $rouge);
        array_push($newMaterial, $vert);
        array_push($newMaterial, $bleu);
        array_push($newMaterial, $reflexion);
        array_push($newMaterial, $transparance);
        array_push($newMaterial, $refraction);
        array_push($_SESSION["allElements"],$newMaterial);
        array_push($_SESSION["allMateriaux"],$newMaterial);
    }
    redirect("../index.php");
}

if(filter_input(INPUT_POST, "showScene", FILTER_SANITIZE_SPECIAL_CHARS)){
    $shownScene = filter_input(INPUT_POST, "scenePicker", FILTER_SANITIZE_SPECIAL_CHARS);
    var_dump($shownScene);
    if($shownScene != "Scènes faites"){
        $_SESSION["shownScene"] = "php/images/".$shownScene.".jpg";
    }
    else{
        echo "dacc";
        $_SESSION["shownScene"] = "test.jpg";
    }
    redirect("../index.php");
}