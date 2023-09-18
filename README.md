# LFU
В данном проекте я реализую свой LFU кэш.

В этой версии я реализовал кэш, основанный на двух списках: кэш - список, состоящий из элементов, каждый из которых хранит в себе количество хитов и список элементов с этим количестовм хитов.
Прочитать об этом алгоритме можно [здесь](https://arpitbhayani.me/blogs/lfu/) или [здесь](https://ieftimov.com/posts/when-why-least-frequently-used-cache-implementation-golang/).

Идельный кэш пока оставлен без изменений.

На вход пользователь дает размер кэша и количество элементов, с которыми кэшу предстоит работать.

Для загрузки и запуска проекта:

```
git clone git@github.com:Pelmeshka127/Cache.git

cd Cache
```

Для загрузки тестов на вход принимаются 3 параметра:
Размер кэша, количество считываемых элементов и количество тестов.

```
make test

./obj/test
```

Для запуска кэша:

```
make cache

./obj/cache <test>
```

Для запуска работы идеального кеша:

```
make ideal_cache

./obj/ideal <test>
```


Сборка кэша, ориентированная для тестов на произодительность:

```
make opt_cache

./obj/cache <test>
```

Сборка идеального кэша, ориентированная для тестов на произодительность:

```
make opt_ideal_cache

./obj/ideal <test>
```

Сборка компаратора двух кэшей:

```
make opt_comparation

./obj/comp <test>
```