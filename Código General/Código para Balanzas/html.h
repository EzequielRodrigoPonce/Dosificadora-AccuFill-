const char* html_code = R"=====(

<!DOCTYPE html>
<html lang="es">

<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>AccuFill</title>

    <!--codigos js para menu e inicio de sesiones-->

    <!-- codigo script js para el menu -->
    <script>
        // Aquí va el código JavaScript
        function showSection(sectionId) {
            // Ocultar todas las secciones
            var sections = document.querySelectorAll('.section');
            sections.forEach(section => {
                section.style.display = 'none';
            });

            // Mostrar la sección seleccionada
            var sectionToShow = document.getElementById(sectionId);
            if (sectionToShow) {
                sectionToShow.style.display = 'block';
            }
        }
        //<!-- fin codigo script js para el menu -->


        //<!-- inicio codigo js para inicio de sesion y registro -->

        // Mostrar formulario de inicio de sesión y ocultar el de registro y perfil
        function showLoginForm() {
            document.getElementById("loginForm").style.display = "block";
            document.getElementById("registerForm").style.display = "none";
            document.getElementById("profile").style.display = "none";

            // Ocultar el recuadro de bienvenida
            document.getElementById("welcomeBox").style.display = "none";
        }

        // Mostrar formulario de registro y ocultar el de inicio de sesión y perfil
        function showRegisterForm() {
            document.getElementById("registerForm").style.display = "block";
            document.getElementById("loginForm").style.display = "none";
            document.getElementById("profile").style.display = "none";

            // Ocultar el recuadro de bienvenida
            document.getElementById("welcomeBox").style.display = "none";
        }

        // Función para realizar el inicio de sesión
        function login() {
            const username = document.getElementById("loginUsername").value;
            const password = document.getElementById("loginPassword").value;

            // Verificamos si se ha registrado en el formulario de registro.
            const registeredUsers = JSON.parse(localStorage.getItem("registeredUsers")) || [];
            const isRegistered = registeredUsers.some(user => user.username === username && user.password === password);

            if (isRegistered) {
                document.getElementById("profileUsername").textContent = `Usuario: ${username}`;
                document.getElementById("loginForm").style.display = "none";
                document.getElementById("profile").style.display = "block";

                // Establecer el estado de sesión como 1 (inicio exitoso)
                sessionStorage.setItem("estadodesesion", 1);

                // Mostrar mensaje de inicio exitoso
                alert("Inicio de sesión exitoso, bienvenido, actualice la pagina para continuar (F5).");

                // Mostrar el recuadro de bienvenida
                document.getElementById("welcomeBox").style.display = "block";
                document.getElementById("welcomeBox").textContent = `Bienvenido ${username}`;
            } else {
                alert("Usuario no registrado, registrese para poder utilizar el equipo.");
            }
        }

        // Función para realizar el registro
        function register() {
            const username = document.getElementById("registerUsername").value;
            const password = document.getElementById("registerPassword").value;

            // Verificar si el usuario ya está registrado
            const registeredUsers = JSON.parse(localStorage.getItem("registeredUsers")) || [];
            const isRegistered = registeredUsers.some(user => user.username === username);

            if (isRegistered) {
                alert("El nombre de usuario ya está en uso.");
            } else {
                registeredUsers.push({ username, password });
                localStorage.setItem("registeredUsers", JSON.stringify(registeredUsers));
                alert("Registro exitoso.");
            }
        }

        // Función para cerrar sesión y mostrar el formulario de inicio de sesión
        function logout() {
            document.getElementById("profile").style.display = "none";
            document.getElementById("loginForm").style.display = "block";

            // Establecer el estado de sesión como 0 (no iniciado)
            sessionStorage.setItem("estadodesesion", 0);

            // Ocultar el recuadro de bienvenida
            document.getElementById("welcomeBox").style.display = "none";

            // Mostrar mensaje de cierre de sesión
            alert("Sesión cerrada correctamente.");
        }

        // Verificar el estado de sesión al cargar la página
        window.onload = function () {
            const estadodesesion = sessionStorage.getItem("estadodesesion");

            if (estadodesesion === "1") {
                const username = document.getElementById("loginUsername").value;
                document.getElementById("profileUsername").textContent = `Usuario: ${username}`;
                document.getElementById("loginForm").style.display = "none";
                document.getElementById("profile").style.display = "block";
                document.getElementById("miseccion").style.display = "block";

                // Mostrar el recuadro de bienvenida
                document.getElementById("welcomeBox").style.display = "block";
                document.getElementById("welcomeBox").textContent = `Bienvenido ${username}`;
            } else {
                // Mostrar solo los botones de inicio de sesión y registro al cargar la página
                showLoginForm();

            }
            if (estadodesesion === "0") {
                document.getElementById("miseccion").style.display = "none";
            }
        };

        //<!-- fin codigo inicio de sesion y registro de js-->



        //ingreso de datos de numeros negativos no permitido y restriccion en el volumen total
        function validarFormularioYRestriccionVolumenTotal() {
            var volumendelRecipiente = parseFloat(document.getElementById("volumendelRecipiente").value);
            var cantidadLiquido1 = parseFloat(document.getElementById("cantidadLiquido1").value);
            var cantidadLiquido2 = parseFloat(document.getElementById("cantidadLiquido2").value);

            if (cantidadLiquido1 < 0 || cantidadLiquido2 < 0 || volumendelRecipiente < 0) {
                 alert("No se permiten números negativos en los campos de dosificación.");
                 return false;
                }

            if (cantidadLiquido1 + cantidadLiquido2 > volumendelRecipiente) {
                 alert("La cantidad ingresada supera el volumen del recipiente.");
                 return false;
                }

    // Si todas las validaciones pasan, el formulario se enviará
            return true;
                }

//fin de las funciones javascript

    </script>


</head>


<body>

    <title>AccuFill</title>

    <style>
        /* titulo superior de la pagina */
        .title {
            text-align: center;
            /* Centrar el texto */
            position: fixed;
            /* Posición fija para que se mantenga en la parte superior */
            top: 0;
            /* Alinear el título en la parte superior */
            left: 50%;
            /* Centrar horizontalmente */
            transform: translateX(-50%);
            /* Ajustar la posición horizontalmente centrada */
            width: 100%;
            /* Ancho del título al 100% para que ocupe todo el ancho de la pantalla */
            padding: 10px 0;
            /* Espacio en la parte superior e inferior del título */
            color: #2d0f4e;
            /* Color del texto del título */
            font-size: 44px;
            /* Tamaño del texto del título */
            font-family: Arial, sans-serif;
            background-color: rgba(23, 216, 136, 0.5);
            /* color del titulo y transparencia. Cambia el último valor (0.5) para ajustar la transparencia */
            box-shadow: 0 0 10px rgba(34, 32, 32, 0.2);
            /* Cambia el último valor (0.2) para ajustar la sombra */
        }


        /* modifico el fondo de la pagina, imagien de fondo, etc */
        body {
            margin: 0;
            padding: 0;
            font-family: Arial, sans-serif;
            background-image: url('https://kibo-capital.com/wp-content/uploads/2017/06/Blowplast-Picture.jpg";');
            background-size: cover;
            background-position: center;
            display: flex;
            justify-content: center;
            align-items: center;
            height: 100vh;
        }

        /* fin modificacion de la hoja de fondo principal */

        /* MODIFICACIONES DE ESTILO A TODO LO REFERENTE CON EL FORMULARIO */
        /* modifico condiciones del formulario */
        .formulario {
            display: none;
            /* Para que no aparezca el formulario al cargar la pagina */
            position: fixed;
            /* Para posicionar el elemento de forma fija en la pantalla */
            left: 0;
            /* Para alinear el elemento a la izquierda de la pantalla */
            top: 50%;
            /* Para centrar verticalmente el elemento en la mitad de la pantalla */
            transform: translateY(-50%);
            /* Para ajustar la posición verticalmente centrada */
            top: 280px;
            /* La cantidad que elija en píxeles hacia arriba*/
            border: 2px solid #143b8f;
            /* ancho del borde de la tabla */
            border-radius: 20px;
            /* redondeo de los bordes de la tabla */
            padding: 20px;
            background-color: rgba(23, 216, 136, 0.5);
            /* Cambia el último valor (0.5) para ajustar la transparencia */
            box-shadow: 0 0 10px rgba(34, 32, 32, 0.2);
            /* Cambia el último valor (0.2) para ajustar la sombra */
            font-weight: bold;
            /* Aplicar negrita */
        }

        /* modifico el recuadro exterior del formulario de las variables*/
        .table-container {
            display: flex;
            align-items: center;
            margin-bottom: 5px;
        }

        /* modifico los recuadroa para las palabras de cada variable */
        .table-container {
            border: 2px solid #0d2c94;
            border-radius: 10px;
            padding: 10px;
        }

        /* esta linea es las variables, V.rec, cntliq1 y cantliq2, modifico los estilos de esas palabras */
        .table-container label {
            flex: 5;
            text-align: left;
            margin-right: 10px;
        }

        /* modifico los espacios en blanco para ingresar las variables */
        .table-container input {
            flex: 1;
            width: 60px;
            /* Ajusta el ancho del recuadro */
            height: 20px;
            /* Ajusta la altura del recuadro */
            border-radius: 20px;
        }

        .submit {
            /*botom enviar*/
            transform: translateY(35%);
            position: static;
            text-align: center;
        }

        /* fin de modificacines para el formulario */


        /* Estilo para el recuadro de datos recibidos */
        .data-box {
            width: 300px;
            /* Ajusta el ancho del recuadro según tus necesidades */
            height: 150px;
            /* Ajusta la altura del recuadro según tus necesidades */
            border: 2px solid #0bbbbb;
            border-radius: 20px;
            /* Ajusta el radio del borde para redondear el recuadro */
            padding: 10px;
            background-color: rgba(23, 216, 136, 0.5);
            /* Fondo semi-transparente */
            box-shadow: 0 0 10px rgba(0, 0, 0, 0.2);
            /* Sombra */
            position: fixed;
            /* Para posicionar el elemento de forma fija en la pantalla */
            left: 0;
            /* Para alinear el elemento a la izquierda de la pantalla */
            top: 50%;
            /* Para centrar verticalmente el elemento en la mitad de la pantalla */
            transform: translateY(-50%);
            /* Para ajustar la posición verticalmente centrada */
            top: 530px;
            /* ajusto la atura de ubicacion del recuadro */
            border: 2px solid #143b8f;
            border-radius: 20px;
            font-weight: bold;
            /* Aplicar negrita */
        }

        .datosrec {
            left: 0;
            margin-top: 17%;
            transform: translateY(-50%);
            position: fixed;
            padding: 5px;
            font-family: Arial, sans-serif;
            font-weight: bold;
            /* Aplicar negrita */
        }

        /* fin de modificaciones para el recuadro de datos recibidos */


        /*  modifico el pie de pagina */
        footer {
            text-align: center;
            margin-top: 45%;
        }

        h4 {
            text-align: center;
        }

        /* fin de modificaciones para el pie de pagina */


        /* NMODIFICACIONES DE ESTILO PARA LOS MENU */
        /* Estilos para los títulos de las secciones del menu*/
        .section h2 {
            font-size: 24px;
            font-weight: bold;
            font-family: Arial, sans-serif;
        }

        /* Estilos para los contenidos de las secciones */
        .section .content {
            display: absolute;
            justify-content: space-around;
            flex-wrap: wrap;
        }

        /* Estilos para cada imagen con descripción */
        .image-with-description {
            margin: 10px;
            cursor: pointer;
            /* Cambiar el cursor al pasar el ratón por encima */
            transition: transform 0.3s ease;
            /* Efecto de transición */
        }

        /* Efecto de sobresalir cuando se pasa el ratón por encima */
        .image-with-description:hover {
            transform: scale(1.1);
        }

        /* fin menu  y los recuadros que lo contienen*/

        /* Estilos para el menú de navegación, (los botodes de cada seccion)*/
        .menu {
            position: absolute;
            top: 0;
            right: 0;
            margin: 20px;
            top: 60px;
        }

        .menu ul {
            list-style: none;
            padding: 0;
        }

        .menu li {
            margin-bottom: 10px;
        }

        .menu a {
            text-decoration: none;
            color: #333;
            font-size: 18px;
        }

        /* Estilos generales para las secciones */
        .section {
            position: absolute;
            text-align: center;
            padding: 17px;
            background-color: rgba(23, 216, 136, 0.5);
            /* Fondo semi-transparente */
            box-shadow: 0 0 10px rgba(0, 0, 0, 0.2);
            display: none;
            /* Ocultar todas las secciones inicialmente */
            top: 100px;
        }

        /* fin de modificaciones para todo lo que corresponde al munu de quienes somos, productos y contacto */



        /* modificaciones para el inicio de sesion y registro */
        .sesion {
            position: fixed;
            font-family: Arial, sans-serif;
            padding: 15px;
            max-width: 300px;
            top: 120px;
            right: 10px;
            background-color: rgba(23, 216, 136, 0.5);
            /* Fondo semi-transparente */
            box-shadow: 0 0 10px rgba(0, 0, 0, 0.2);
            border: 2px solid #0bbbbb;
            border-radius: 20px;
            font-weight: bold;
        }

        .sesion input {
            width: 100%;
            margin-bottom: 10px;
            padding: 5px;

        }

        .sesion button {
            width: 100%;
            padding: 10px;
            background-color: #4CAF50;
            color: white;
            border: none;
            cursor: pointer;
        }

        .sesion button:hover {
            background-color: #45a049;
        }

        #profile {
            display: none;
        }

        /* Estilos para el recuadro de bienvenida */
        #welcomeBox {
            display: none;
            border: 2px solid #4CAF50;
            background-color: #e9f5e9;
            padding: 10px;
            border-radius: 8px;
            margin-bottom: 10px;
        }

        /* fin modificaciones para el inicio de sesion y registro*/

        /* fin de modificacionde de estilos */
    </style>




    <!-- seccion de munu -->
    <!------------------------------------------------------------------------------->
    <!-- Sección 1: Quienes Somos -->
    <div class="section" id="quienesSomos">
        <h2>Quienes Somos</h2>
        <div class="content">
            <div class="image-with-description">
                <img src="https://th.bing.com/th/id/R.f0057533fa2ac82e391d71ce3783fc5f?rik=Zr0SCxJKsjvaoQ&pid=ImgRaw&r=0"
                    alt="Imagen 1">
                <p>Entendemos que cada negocio tiene requerimientos únicos </p>
                <p>y nos enorgullecemos de ofrecer un servicio personalizado y adaptado a
                <p>cada cliente.</p>
            </div>

        </div>
    </div>

    <!-- Sección 2: Productos -->
    <div class="section" id="productos">
        <h2>Productos</h2>
        <div class="content">
            <div class="image-with-description">
                <img src="https://5.imimg.com/data5/HY/JW/MY-4027994/micro-peristaltic-pump-500x500.jpg"
                    alt="Producto 1">
                <p>Nuestros productos de dosificadores son la elección perfecta</p>
                <p>en eficiencia y precisión. </p>
            </div>
        </div>
    </div>

    <!-- Sección 3: Contacto -->
    <div class="section" id="contacto">
        <h2>Contacto</h2>
        <div class="content">
            <!-- Aquí puedes agregar el mapa de Google Maps -->
            <img src="https://th.bing.com/th/id/OIP.4ywwdvwC4p3NS8JBiopl7wHaKD?pid=ImgDet&rs=1" alt="">

        </div>
    </div>

    <!-- Botones de navegación -->
    <div class="menu">
        <button onclick="showSection('quienesSomos')">Quienes Somos</button>
        <button onclick="showSection('productos')">Productos</button>
        <button onclick="showSection('contacto')">Contacto</button>
    </div>

    <script src="script.js"></script> <!-- Enlazar archivo de script JavaScript -->
    <!-----------------fin seccion menu-------------------------------------------------------------->



    <!-- inicio de sesion y registro -->
    <div class="sesion">
        <div id="loginForm">
            <h2>Iniciar sesión</h2>
            <input type="text" id="loginUsername" placeholder="Usuario" required>
            <input type="password" id="loginPassword" placeholder="Contraseña" required>
            <button onclick="login()">Iniciar sesión</button>
            <p>¿No tienes una cuenta? <a href="#" onclick="showRegisterForm()">Regístrate aquí</a></p>
        </div>

        <div id="registerForm">
            <h2>Registro</h2>
            <input type="text" id="registerUsername" placeholder="Usuario" required>
            <input type="password" id="registerPassword" placeholder="Contraseña" required>
            <button onclick="register()">Registrarse</button>
            <p>¿Ya tienes una cuenta? <a href="#" onclick="showLoginForm()">Inicia sesión aquí</a></p>
        </div>

        <div id="profile">
            <div id="welcomeBox"></div>

            <h2></h2>
            <p id="profileUsername"></p>
            <button onclick="logout()">Cerrar sesión</button>
        </div>
    </div>

    <script src="script.js"></script> <!-- Enlazar archivo de script JavaScript -->

    <!-- fin codigo inicio de sesion y registro -->


    <!------------------------------------------------------------------------------->
    <!--tabla para enviar los datos, con la etiqueta form identifico que es un formulario-->
    <form id="miseccion" class="formulario" action="/procesar" method="POST" onsubmit="return validarFormularioYRestriccionVolumenTotal();">
        <!--onsubmit solo puede haber uno solo, debo hacer las funciones que vayn ahoi todas juntas--->
        <div class="table-container">
            <label for="volumendelRecipiente">Volumen del recipiente:</label>
            <input type="number" id="volumendelRecipiente" name="Volumen_del_recipiente">
        </div>
        <div class="table-container">
            <label for="cantidadLiquido1">Cantidad liquido 1:</label>
            <input type="number" id="cantidadLiquido1" name="Cantidad_liquido_1">
        </div>
        <div class="table-container">
            <label for="cantidadLiquido2">Cantidad liquido 2:</label>
            <input type="number" id="cantidadLiquido2" name="Cantidad_liquido_2">
        </div>
        <div class="submit">
            <input type="submit" value="Enviar">
            <input type="reset" value="Borrar">
        </div>
    </form>

    <!------------------------------------------------------------------------------->


    <!-- Datos ingresados.   -->
    <div class="data-box">
        <h2>Datos ingresados:</h2>
        <table border="1">
            <tr>
                <th>Volumen del recipiente</th>
                <th>Cantidad líquido 1</th>
                <th>Cantidad líquido 2</th>
            </tr>
            <tr>
                <td>%VOLUMEN_RECIP%</td>
                <td>%CANTIDAD_LIQUIDO_1%</td>
                <td>%CANTIDAD_LIQUIDO_2%</td>
            </tr>
        </table>
        <!-- Aquí se mostrarán los datos recibidos desde el puerto serial -->
    </div>


    <!-- TITULO PRINCIPAL   -->
    <div class="title">
        Dosificadores AccuFill
    </div>


    <!-- pie de pagina -->
    <footer>
        <div class="flex-container">
            <a href="https://www.instagram.com/your_instagram_account">
                Instagram -
            </a>

            <a href="https://www.facebook.com/your_facebook_page">
                Facebook -
            </a>
            <a href="https://wa.me/your_whatsapp_number">
                WhatsApp
            </a>
        </div>
        <h4>Todos los derechos reservados ©</h4>
    </footer>
    <!------------------------------------------------------------------------------->



</body>

</html>

  )=====";
