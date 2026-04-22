// Складні класи підсистеми інтернет-магазину
public class InventorySystem {
    public bool CheckStock(string productId) {
        System.Console.WriteLine($"Перевірка наявності товару {productId} на складі...");
        return true; 
    }
}
public class PaymentGateway {
    public bool ProcessPayment(string accountId, decimal amount) {
        System.Console.WriteLine($"Обробка платежу на суму {amount} грн...");
        return true; 
    }
}
public class ShippingService {
    public void ArrangeShipping(string productId, string address) {
        System.Console.WriteLine($"Формування накладної для доставки товару за адресою: {address}");
    }
}
public class NotificationService {
    public void SendReceipt(string email) {
        System.Console.WriteLine($"Відправка чека на електронну пошту: {email}");
    }
}

// Клас-Фасад, що приховує складну логіку оформлення замовлення
public class OrderFacade {
    private InventorySystem _inventory = new InventorySystem();
    private PaymentGateway _payment = new PaymentGateway();
    private ShippingService _shipping = new ShippingService();
    private NotificationService _notification = new NotificationService();
    public bool PlaceOrder(string productId, decimal price, string email, string address) {
        if (!_inventory.CheckStock(productId)) return false;
        
        if (_payment.ProcessPayment(email, price)) {
            _shipping.ArrangeShipping(productId, address);
            _notification.SendReceipt(email);
            return true;
        }
        return false;
    }
}

class Program {
    static void Main() {
        var shopApi = new OrderFacade();
        
        bool isSuccess = shopApi.PlaceOrder(
            productId: "LAPTOP-X200", 
            price: 45000.00m, 
            email: "client@nure.ua", 
            address: "м. Харків, пр. Науки, 14"
        );
        System.Console.WriteLine(isSuccess ? "Замовлення успішне!" : "Помилка замовлення.");
    }
}
