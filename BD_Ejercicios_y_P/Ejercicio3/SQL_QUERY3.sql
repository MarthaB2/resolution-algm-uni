use ejercicio3;

-- 1. Indique la cantidad de productos que tiene la empresa.

select count(*) as cantProductos from producto;

-- 2. Indique la cantidad de productos en estado en stock que tiene la empresa.

select count(*) as cantProductosEnStock from producto
where Estado='stock';

-- 3. Indique los productos que nunca fueron vendidos.
select * from producto;
select * from detalle_venta;

select * from producto
where Id_producto not in ( select Id_producto from detalle_venta);

-- 4. Indique la cantidad de unidades que fueron vendidas de cada producto.
select * from detalle_venta;
select Id_producto, sum(Cantidad) as cantUniV 
from detalle_venta
group by Id_producto;

-- 5. Indique cual es la cantidad promedio de unidades vendidas de cada producto.
select * from detalle_venta;

select Id_producto, avg(Cantidad) as cantUniV 
from detalle_venta
group by Id_producto;

-- 6. Indique quien es el vendedor con mas ventas realizadas.

select Id_vendedor, count(Nro_factura) as cantVent from venta 
group by Id_vendedor order by count(Nro_factura) desc;

create view ventas_x_vendedor
as 
select v.Id_vendedor, count(Nro_factura) as 'CantVentas'
from venta v
group by v.Id_vendedor;


-- Obtengo el mayor
select *
from ventas_x_vendedor vxv
where vxv.CantVentas=(select max(cantVentas) from ventas_x_vendedor);




-- 7. Indique todos los productos de lo que se hayan vendido más de 15.000 unidades.

select * from detalle_venta;
select Id_producto, sum(Cantidad) as cantUniV from detalle_venta
group by Id_producto having sum(Cantidad)>15;

-- 8. Indique los clientes que le han comprado a todos los vendedores.
select c.* from cliente c
where NOT EXISTS ( select v.* from vendedor v
					where NOT EXISTS (select * from venta vta
								where vta.Id_vendedor=v.Id_vendedor and 
                                vta.Id_cliente=c.Id_cliente));

-- 9.Genere un SP que permita crear un nuevo vendedor pasando los parametros.

delimiter //

CREATE PROCEDURE sp_nuevoVendedor(
        IN Nombre varchar(50), 
        IN Apellido varchar(50), 
        IN Dni bigint
)
BEGIN
	DECLARE id int ;
    SET id = (SELECT IFNULL(MAX(id_vendedor),0) FROM vendedor);
    
	INSERT INTO vendedor (id_vendedor,Nombre,Apellido,Dni)
	VALUES(id+1,Nombre, Apellido, Dni);
END //

delimiter ;

-- Invocar el procedimiento 
call sp_nuevoVendedor('Juan', 'Pérez', 12345678);

-- Verificar la inserción
select * from vendedor;

-- Utiliza DELIMITER //  al principio y DELIMITER ; al final para permitir la correcta interpretación del cuerpo del procedimiento.

-- 10. Obtenga los productos que fueron vendidos a 3 clientes
select * from detalle_venta;
select * from venta;
select dv.Id_producto from detalle_venta dv
inner join venta v on dv.Nro_factura=v.Nro_factura
group by dv.Id_producto having count(distinct v.Id_cliente)=3;

-- 11. Genere una funci—n que al tener un nro de factura nos diga el monto total de venta.
delimiter //

create function f_ObtenerTotalVenta(
				Nro_factura int)
returns int
deterministic
begin
	declare montoTotal int;
    set montoTotal  = (select sum(dv.Precio_unitario*dv.cantidad) from detalle_venta dv
						where dv.Nro_factura=Nro_factura
                        );
	return montoTotal;
end // 

delimiter ;
 
select * from detalle_venta;
select f_ObtenerTotalVenta(10);


/*11. La tabla de ventas y detalle se vuelven muy pesadas asi que periodicamente borramos registros.
Pero no queremos perder la información, asi que lo necesitamos mandar a un historico de Ventas. 
Genere las 2 tablas y automatice el proceso.  */


-- CREATE TABLE historico_Venta
CREATE TABLE Historico_Venta(
	Nro_factura BIGINT,
	Id_cliente INT,
	Id_vendedor INT,
	Fecha DATE ,
	PRIMARY KEY(nro_factura),
	FOREIGN KEY(id_cliente)REFERENCES cliente(id_cliente),
	FOREIGN KEY(id_vendedor)REFERENCES vendedor(id_vendedor)
);


-- CREATE TABLE historico_DetalleVenta
CREATE TABLE Historico_Detalle_venta(
	Nro_factura BIGINT,
	Nro_detalle BIGINT,
	Id_producto INT,
	Cantidad INT,
	Precio_unitario INT,
	PRIMARY KEY(nro_factura, nro_detalle),
	FOREIGN KEY(nro_factura)REFERENCES historico_venta(nro_factura),
	FOREIGN KEY(id_producto)REFERENCES producto(id_producto)
);


DELIMITER //

CREATE TRIGGER vta_eliminada
AFTER DELETE ON venta
FOR EACH ROW
BEGIN
    -- Insertar datos en historico_Venta
    INSERT INTO Historico_Venta (Nro_factura, Id_cliente, Id_vendedor, Fecha)
    VALUES (OLD.Nro_factura, OLD.Id_cliente, OLD.Id_vendedor, OLD.Fecha);

    -- Insertar datos en historico_Detalle_Venta
    INSERT INTO Historico_Detalle_Venta (Nro_factura, Nro_detalle, Id_producto, Cantidad, Precio_unitario)
    SELECT dv.Nro_factura, dv.Nro_detalle, dv.Id_producto, dv.Cantidad, dv.Precio_unitario
    FROM Detalle_venta dv
    WHERE dv.Nro_factura = OLD.Nro_factura;
END //

DELIMITER ;

INSERT INTO venta(Nro_factura, Id_cliente, Id_vendedor, Fecha) VALUES(26,3,2,'2020-06-03');
DELETE FROM venta WHERE Nro_factura=26;
select * from Historico_Detalle_Venta;
select * from Historico_Venta;
/*
AFTER DELETE ON venta: Este trigger se ejecuta después de que se elimina un registro de la tabla venta.
FOR EACH ROW: Este trigger Se ejecuta para cada fila eliminada.
OLD: Se refiere a los valores del registro que se está eliminando.
*/
