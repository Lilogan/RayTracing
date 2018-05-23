<p id="elementTitle">Elements ajoutés</p>

<?php
//var_dump($_SESSION["allElements"]);
foreach($_SESSION["allElements"] as $current){
    if($current[0] == "SP"){
        
        echo "<p class='allElementTitle'>Spheroide:</p>";
        echo "<div class='anElement'>";
        echo "\t";
        echo "rayon: (".$current[1].",".$current[2].",".$current[3].")";
        echo "<br/>";
        echo "\t centre: (".$current[4].",".$current[5].",".$current[6].")";
        echo "<br/>";
        echo "\t materiaux: ".$current[7];
        echo "</div>";
    }
    else if($current[0] == "POLY"){
        echo "<p class='allElementTitle'>Polygone:</p>";
        echo "<div class='anElement'>";
        echo "\t";
        echo "Nom: ".$current[1];
        echo "<br/>";
        for($i = 1; $i <= $current[2]; $i++){
            echo "\t";
            echo "point".$i.": (".$current[3*$i].",".$current[3*$i+1].",".$current[3*$i+2].")";
            echo "<br/>";
        }
        echo "</div>";
    }
    else if($current[0] == "LAMPE"){
        
        echo "<p class='allElementTitle'>Lampe:</p>";
        echo "<div class='anElement'>";
        echo "\t";
        echo "position: (".$current[1].",".$current[2].",".$current[3].")";
        echo "<br/>";
        echo "\t Couleur: (".$current[4].",".$current[5].",".$current[6].")";
        echo "<br/>";
        echo "</div>";
    }
    else if($current[0] == "PLAN"){
        
        echo "<p class='allElementTitle'>Plan:</p>";
        echo "<div class='anElement'>";
        echo "\t";
        echo $current[1]."x+ ".$current[2]."y + ".$current[3]."z + ".$current[4]." = 0";
        echo "<br/>";
        echo "\t";
        echo "materiaux: ".$current[5];
        echo "</div>";
    }
    else if($current[0] == "SO"){
        echo "<p class='allElementTitle'>Solide:</p>";
        echo "<div class='anElement'>";
        for($i =1 ; $i <= $current[1]; $i++){       
            echo "\t";
            echo "polynome ".$i.": ".$current[$i+1][1];
            echo "<br/>";
        }
        echo "</div>";
    }
    else if($current[0] == "MAT"){
        echo "<p class='allElementTitle'>Materiaux:</p>";
        echo "<div class='anElement'>";     
        echo "\t";
        echo "Nom: ".$current[1];
        echo "<br/>";
        echo "\t";
        echo "couleur: (".$current[2].", ".$current[3].", ".$current[4].")";
        echo "<br/>";
        echo "\t";
        echo "propriétés :(".$current[5].", ".$current[6].", ".$current[7].")";
        echo "</div>";
        }
        
}
?>

<form method="POST" action="./php/controller.php">
    <div class='inputParameter'>
    <input type='submit' value='Executer' name='execute'/>
    <input type='submit' value='Recommencer' name='restart'/>
    </div>
</form>