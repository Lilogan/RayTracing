<p id="elementTitle">Ajouter la camera</p>

<p class="elementDesc"></p>

<form class="formParameters" method="POST" action="./php/controller.php">
    <div class="inputParameter">
        <label for="vecX">Vecteur X:</label>   
        <input type="number" id="vecX" name='vecX' step="0.1"/>
    </div>
    <div class="inputParameter">
        <label for="vecY">Vecteur Y:</label>
        <input type="number" id="vecY" name='vecY' step="0.1"/>
    </div>
    <div class="inputParameter">
        <label for="vecZ">Vecteur Z:</label>
        <input type="number" id="vecZ" name='vecZ' step="0.1"/>
    </div>
    
    <div class="inputParameter">
        <label for="ptX">Point X:</label>
        <input type="number" id="ptX" name='ptX' step="0.1"/>
    </div>
    <div class="inputParameter">
        <label for="ptY">Point Y:</label>
        <input type="number" id="ptY" name='ptY' step="0.1"/>
    </div>
    <div class="inputParameter">
        <label for="ptZ">Point Z:</label>
        <input type="number" id="ptZ" name='ptZ' step="0.1"/>
    </div>
    <div class="inputParameter">
        <label for="resX">resolution X:</label>
        <input type="number" id="resX" name='resX' step="1"/>
    </div>
    <div class="inputParameter">
        <label for="resY">resolution Y:</label>
        <input type="number" id="resY" name='resY' step="1"/>
    </div>
    
    <div class="inputParameter">
        <input type="submit"  name="addCam" value="Ajouter"/>
    </div>
</form>



