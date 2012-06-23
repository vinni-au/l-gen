#ifndef MCR_HPP
#define MCR_HPP

#undef UNICODE
#include <windows.h>

//максимальная длина входного слова
const unsigned char MAX_WORD_LEN=32;
//максимальное количество слов в парадигме
const unsigned char MAX_WORD_COUNT=200;

//! Стуктура, определяющая одно слово и его грамматические характеристики
struct Word
{
    //! Словоформа
    char wordForm[MAX_WORD_LEN];
    //! Постоянная грамматическая характеристика (часть речи и т.п.)
    unsigned char cid;
    //! Переменная грамматическая характеристика (падеж и т.п.)
    unsigned char vid;
    //! Опциональность слова (если есть)
    char virt;
    //! Системное - явно не используется
    unsigned char para;
};

//! Структура используется для добавления и считывания парадигмы (слова)
struct Words
{
    //! Слова
    Word inlex[MAX_WORD_COUNT];
    //! Их количество
    int count;
};

//! Структура, определяющая уникальный идентификатор для одной словоформы
struct WordForm
{
    //! Ссылка на лексему (max 20 бит)
    unsigned long pLexem;
    //! Ссылка на номер слова в парадигме
    unsigned char pN;
};

//! Общая структура идентификаторов
struct WordForms
{
    //! Словоформы
    WordForm ids[MAX_WORD_COUNT];
    //! Их количество
    int count;
};

// InitMcr() - инициализировать словарь mcr
typedef int (*p1Func)();

// LoadMcr() - загрузить словарь mcr
typedef int (*p2Func)(const char * s);

// SaveMcr() - сохранить словарь mcr
typedef int (*p3Func)(const char * s);

// FindID - поиск слова s в словаре mcr,
// возвращает int количество найденых слов и ids
// (уникальный идентификтор слова = уникальный идентификатор леммы + номер слова в парадигме)
// Используйте полученные идентификаторы для получения грамматических характеристик
// слова или возврата всей парадигмы
typedef int (*p4Func)(const char * s, WordForms* ids);

// GetByID - для идентификатора id, функция возвращает грамматические характеристики,
// лемму или всю парадигмы в outdata
// :: gh_only = true - возвращать только грамматические характеристики
// :: gh_only = false - возвратить грамматические характеристики для id и лемму (win1251)
// :: all = true  - поместить в wout всю парадигму для указанного id
// с грамматическими характериситками, доступно только для словарей без пометы ReadOnly
typedef int (*p5Func)(const WordForm id, bool gh_only, bool all, Words *outdata);

// ROnly Проверка является ли подключенный словарь - словарем только для чтения (ReadOnlyDict)
typedef bool (*p6Func)();

// AddPara - добавление парадигмы в словарь
typedef int (*p7Func)(Words *indata);

// 3Space - проверка свободного места в словаре, если любой из аргументов
// близок к 100% то добавление парадигм будет вскоре невозможно
typedef int (*p8Func)(unsigned char * ar1, unsigned char * ar2, unsigned char * ar3);

// Информация о версии mcr.dll
typedef int (*p9Func)(char * s);

//Строка постоянной грамматической характеристики
typedef char * (*p10Func)(const unsigned char cid);

//Строка переменной грамматической характеристики
typedef char * (*p11Func)(const unsigned char cid, const unsigned char vid);

// Нахождение словоформ по заданной грамматической характеристике (только для не ReadOnly словарей)
// lnk - номер парадигмы
// const_gh - код постоянной грамматическрй характеристики (const_gh=0 - любая)
// var_gh - переменная гр. характеристика
// all=false - вернуть только первую найденную словоформу
typedef int (*p12Func)(const int plexem, unsigned char const_gh,
                       unsigned char var_gh, const bool all, Words *outdata);

//! Морфоанализатор
class MCR
{
public:

    //! Имя существительное
    enum Noun
    {
        //! М.р. неодуш.
        NounMasculineInanimate = 1,
        //! М.р. одуш.
        NounMasculineAnimate = 2,
        //! Ж.р. неодуш.
        NounFeminineInanimate = 3,
        //! Ж.р. одуш.
        NounFeminineAnimate = 4,
        //! С.р. неодуш.
        NounNeuterInanimate = 5,
        //! С.р. одуш.
        NounNeuterAnimate = 6,
        //! М.-ж.р. неодуш.
        NounMasculineFeminineInanimate = 7,
        //! М.-ж.р. одуш.
        NounMasculineFeminineAnimate = 8,
        //! М.-с.р. неодуш.
        NounMasculineNeuterInanimate = 9,
        //! М.-с.р. одуш.
        NounMasculineNeuterAnimate = 10,
        //! Ж.-с.р. неодуш.
        NounFeminineNeuterInanimate = 11,
        //! Ж.-с.р. одуш.
        NounFeminineNeuterAnimate = 12,
        //! Только мн.ч. неодуш.
        NounPluralOnlyInanimate = 13,
        //! Только мн.ч. одуш.
        NounPluralOnlyAnimate = 14,
        //! Существительное *
        Noun = 15
    };

    //! Глагол
    enum Verb
    {
        //! Несов. невозвр, I
        VerbImperfectiveIrrevocableI = 40,
        //! Несов. невозвр, II
        VerbImperfectiveIrrevocableII = 41,
        //! Несов. возвр. I
        VerbImperfectiveReflexiveI = 42,
        //! Несов. возвр. II
        VerbImperfectiveReflexiveII = 43,
        //! Сов. невозвр. I
        VerbPerfectiveIrrevocableI = 44,
        //! Сов. невозвр. II
        VerbPerfectiveIrrevocableII = 45,
        //! Сов. возвр. I
        VerbPerfectiveReflexiveI = 46,
        //! Сов. возвр. II
        VerbPerfectiveReflexiveII = 47,
        //! Сов.-несов. (двухвидовой) I
        VerbTwoWayI = 48,
        //! Сов.-несов. (двухвидовой) II
        VerbTwoWayII = 49,
        //! (Сов.)-несов. возвр. I (совершенность носит потенциальный характер)
        VerbPotentiallyPerfectiveReflexiveI = 50,
        //! (Сов.)-несов. возвр. II (совершенность носит потенциальный характер)
        VerbPotentiallyPerfectiveReflexiveII = 51
    };

    //! Остальные части речи
    enum OtherWordClasses
    {
        //! Наречие
        Adverb = 30,
        //! Союз
        Conjuction = 31,
        //! Междометие
        Interjection = 32,
        //! Частица
        Particle = 33,
        //! Предлог
        Preposition = 34,
        //! Предикат
        Predicate = 35,
        //! Вводное слово
        Parenthesis = 36,
        //! Неизменяемое слово
        Unchangeable = 37
    };

    //! Переменная грамматическая характеристика для существительного
    enum NounModifiers
    {
        //! Все формы одинаковы
        SameForms = 0,
        //! Ед. число, И.П.
        SingularNorminative = 1,
        //! Ед. число, Р.П.
        SingularGenitive = 2,
        //! Ед. число, Д.П.
        SingularDative = 3,
        //! Ед. число, В.П.
        SingularAccusative = 4,
        //! Ед. число, Т.П.
        SingularInstrumental = 5,
        //! Ед. число, П.П.
        SingularPrepositional = 6,
        //! Мн. число, И.П.
        PluralNorminative = 7,
        //! Мн. число, Р.П.
        PluralGenitive = 8,
        //! Мн. число, Д.П.
        PluralDative = 9,
        //! Мн. число, В.П.
        PluralAccusative = 10,
        //! Мн. число, Т.П.
        PluralInstrumental = 11,
        //! Мн. число, П.П.
        PluralPrepositional = 12,
        //! Только мн. число, все формы одинаковы
        PluralOnlySameForms = 13
    };

    //! Переменная грамматическая характеритика для глагола
    enum VerbModifiers
    {
        //! Инфититив
        Infinitive = 1,
        //! Наст.вр. ед.ч. 1 лицо
        PresentSingular1 = 2,
        //! Наст.вр. ед.ч. 2 лицо
        PresentSingular2 = 3,
        //! Наст.вр. ед.ч. 3 лицо
        PresentSingular3 = 4,
        //! Наст.вр. мн.ч. 1 лицо
        PresentPlural1 = 5,
        //! Наст.вр. мн.ч. 2 лицо
        PresentPlural2 = 6,
        //! Наст.вр. мн.ч. 3 лицо
        PresentPlural3 = 7,
        //! Пр.вр. ед.ч. всех лиц м.р.
        PastSingularMasculine = 8,
        //! Пр.вр. ед.ч. всех лиц ж.р.
        PastSingularFeminine = 9,
        //! Пр.вр. ед.ч. всех лиц ср.р.
        PastSingularNeuter = 10,
        //! Пр.вр. мн.ч. всех лиц всех родов
        PastPlural = 11,
        //! Повел. 2 лицо ед.ч.
        ImperativeSingular2 = 12,
        //! Повел. 2 лицо мн.ч.
        ImperativePlural2 = 13,
        //! Повел. 1 лицо мн.ч. (к одному)
        ImperativePlural1ToOne = 14,
        //! Повел. 1 лицо мн.ч. (ко многим)
        ImperativePlural1ToMany = 15,
        //! Буд.вр. ед.ч. 1 лицо
        FutureSingular1 = 16,
        //! Буд.вр. ед.ч. 2 лицо
        FutureSingular2 = 17,
        //! Буд.вр. ед.ч. 3 лицо
        FutureSingular3 = 18,
        //! Буд.вр. мн.ч. 1 лицо
        FuturePlural1 = 19,
        //! Буд.вр. мн.ч. 2 лицо
        FuturePlural2 = 20,
        //! Буд.вр. мн.ч. 3 лицо
        FuturePlural3 = 21,
        //! Наст.буд.вр. ед.ч. 1 лицо
        PresentFutureSingular1 = 25,
        //! Наст.буд.вр. ед.ч. 2 лицо
        PresentFutureSingular2 = 26,
        //! Наст.буд.вр. ед.ч. 3 лицо
        PresentFutureSingular3 = 27,
        //! Наст.буд.вр. мн.ч. 1 лицо
        PresentFuturePlural1 = 28,
        //! Наст.буд.вр. мн.ч. 2 лицо
        PresentFuturePlural2 = 29,
        //! Наст.буд.вр. мн.ч. 3 лицо
        PresentFuturePlural3 = 30
    };

    // Инициализация морфоанализатора (требует наличия mcr.dll в папке ./data/)
    MCR();
    ~MCR();
    // Является ли загруженный словарь словарём только для чтения
    bool readOnly;
    //! Загрузить словарь
    bool LoadVocabulary(const char *filename);

    //! Сохранить словарь
    bool SaveVocabulary(const char *filename);

    //! Найти словоформы для слова
    WordForms* FindWordForms(const char *word);

    //! Получение словоформ и/или грамматических характеристик
    // grCharOnly - возвращать ли толькь грамматические характеристики
    // all - возвратить ли всю парадигму
    Words* GetLexemByID(const WordForm id, const bool grCharOnly, const bool all);

    //! Добавить парадигму в словарь
    bool AddParadigm(Words *lexData);

    //! Получить строку постоянной грамматической характеристики
    char* ConstGrammarChar(const unsigned char cid);

    //! Получить строку переменной грамматической характеристики
    char* VarGrammarChar(const unsigned char cid, const unsigned char vid);

    //! Найти лексемы
    Words* FindLexems(const int pn, const unsigned char cid,
                          const unsigned char vid, const bool all);
    //! Найти лемму для слова
    static Word* FindLemma(const char* word);

    char* createWordForm(const char *word, int vid);

private:
    p1Func pInit;
    p2Func pLoad;
    p3Func pSave;
    p4Func pFind;
    p5Func pGetById;
    p6Func pROnly;
    p7Func pAdd;
    p8Func pSpace;
    p9Func pVer;
    p10Func pCGD;
    p11Func pVGD;
    p12Func pFGD;
    HINSTANCE hDll;    
    bool LoadMCRDLL();    
    void ReleaseMCRDLL();
};

#endif // MCR_HPP
