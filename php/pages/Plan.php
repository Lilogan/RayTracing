<p id="elementTitle">Ajouter un Plan</p>

<p class="elementDesc">Ax+By+Cz+D=0</p>

<form id="formParameters" method="POST" action="./php/controller.php">
    <div class="inputParameter">
        <label for="A">A:</label>   
        <input type="number" id="A" name='A' step="0.1"/>
    </div>
    <div class="inputParameter">
        <label for="B">B:</label>   
        <input type="number" id="B" name='B' step="0.1"/>
    </div>
    <div class="inputParameter">
        <label for="C">C:</label>   
        <input type="number" id="C" name='C' step="0.1"/>
    </div>
    <div class="inputParameter">
        <label for="D">D:</label>   
        <input type="number" id="D" name='D' step="0.1"/>
    </div>
    <div class="inputParameter">
        <select name='materiaux'>
            <?php
               foreach($_SESSION["allMateriaux"] as $mat){
                   echo "<option>".$mat[1]."</option>";
               }
            ?>
        </select>
    </div>

    <div class="inputParameter">
        <input type="submit"  name="addPlan" value="Ajouter"/>
    </div>
</form>



