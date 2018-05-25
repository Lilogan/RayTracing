<html>
<head>
  <title>RayTracing</title>
  <link rel="stylesheet" href="./php/style.css"/>
  <meta charset="utf-8"/>
</head>
<body>
  <header>
    <div id="leftHeader">
        <form class="formHeader" method="POST" action="./php/controller.php">
          <select name="typePicker">
            <option>Creer Scène</option>
            <option>Lampe</option>
            <option>Camera</option>
            <option>Spheroide</option>
            <option>Polygone</option>
            <option>Plan</option>
            <option>Solide</option>
            <option>Materiaux</option>
          </select>
          <input type="submit" name="chooseType" value="Type de structure"/>
        </form>
    </div>
    <div id="centerHeader">
        RayTracing
    </div>
    <div id="rightHeader">
      <form class="formHeader" method="POST" action="./php/controller.php">
        <select name="scenePicker">
          <option>Scènes faites</option>
          <option>Scène 2</option>
          <option>Scène 3</option>
        </select>
        <input type="submit" name="showScene" value="Voir"/>
      </form>
  </div>
  </header>

    <div id="content">
        <div id="left">
            <div id="addElement">
                <?php
                    if(isset($_SESSION["chosenType"]) && $_SESSION["chosenType"] != "Creer Scène"){
                       include("./php/pages/".$_SESSION["chosenType"].".php");
                    }
                    else{
                        include("./php/pages/Lampe.php");
                    }
                ?>
            </div>
            <div id="allElements">
                <?php
                    include("./php/pages/allElements.php")
                ?>
            </div>
        </div>
        <div id="right">
            <?php
             if(file_exists($_SESSION["shownScene"]) && $_SESSION["shownScene"] != NULL){
                echo "<img src='".$_SESSION["shownScene"]."'/>";
             }
             else if($_SESSION["chosenType"] != NULL){
               include("./php/pages/showImage.php");
             }

            ?>
        </div>
    </div>
</body>
</html>
