# kernel_loader.S
.globl loader
loader:
    mov $msg, %edx  # Указываем адрес строки "Loading kernel..."
    mov $0x0e, %ah  # Устанавливаем номер прерывания для вывода символа
    int $0x10       # Вызываем прерывание для вывода символа
    ret

msg:
    .ascii "Loading kernel..."
```