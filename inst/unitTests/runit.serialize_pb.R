## Jeroen Ooms and Dirk Eddelbuettel

test.serialize_pb <- function() {
    ##verify that rexp.proto is loaded
    RProtoBuf:::pb(rexp.REXP)

    ##serialize a nested list
    x <- list(foo=cars, bar=Titanic)
    checkEquals(unserialize_pb(serialize_pb(x, NULL)), x)

    ##a bit of everything, copied from jsonlite package
    set.seed('123')
    myobject <- list(
        mynull = NULL,
        mycomplex = lapply(eigen(matrix(-rnorm(9),3)), round, 3),
        mymatrix = round(matrix(rnorm(9), 3),3),
        myint = as.integer(c(1,2,3)),
        mydf = cars,
        mylist = list(foo='bar', 123, NA, NULL, list('test')),
        mylogical = c(TRUE,FALSE,NA),
        mychar = c('foo', NA, 'bar'),
        myemptychar = character(0),
        somemissings = c(1,2,NA,NaN,5, Inf, 7 -Inf, 9, NA),
        myrawvec = charToRaw('This is a test'),
        myS4 = asS4("test")
    )

    checkEquals(unserialize_pb(serialize_pb(myobject, NULL)), myobject)
}

test.serialize_pb.alldatasets <- function() {
    datasets <- as.data.frame(data(package="datasets")$results)
    datasets$name <- sub("\\s+.*$", "", datasets$Item)

    encoded.datasets <- sapply(datasets$name,
                               function(x) serialize_pb(get(x), NULL))

    unserialized.datasets <- sapply(encoded.datasets, unserialize_pb)

    checkTrue(all(sapply(names(unserialized.datasets),
                         function(name) identical(get(name),
                                                  unserialized.datasets[[name]]))))
}


## this was issue #37 reported and fixed by Jeffrey Shen
test.serialize.sublist <- function() {
    x <- packageVersion("RProtoBuf")
    checkIdentical(x, unserialize_pb(serialize_pb(x, NULL)), msg="checking sublists")
}

test.serialize.posixlt <- function() {
    x <- as.POSIXlt("1970-01-01T00:00:00Z")
    checkIdentical(x, unserialize_pb(serialize_pb(x, NULL)), msg="checking posixlt")
}