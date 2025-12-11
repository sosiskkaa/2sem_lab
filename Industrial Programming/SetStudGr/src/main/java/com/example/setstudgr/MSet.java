package com.example.setstudgr;

import java.io.*;
import java.util.Arrays;
import java.util.ArrayList;
import java.util.List;

public class MSet<T extends Comparable<T>> implements Serializable
{
    private List<T> elements;

    public MSet() {
        this.elements = new ArrayList<>();
    }

    public MSet(List<T> elements) {
        this.elements = new ArrayList<>(elements);
        sortElements();
    }

    public MSet(MSet<T> other) {
        this.elements = new ArrayList<>(other.elements);
    }

    public int size() {
        return elements.size();
    }

    public T get(int index) {
        return elements.get(index);
    }

    public void add(T element) {
        elements.add(element);
        sortElements();
    }

    private void sortElements() {
        elements.sort(Comparable::compareTo);
    }
    
    public MSet<T> union(MSet<T> other) {
        List<T> result = new ArrayList<>();
        int i = 0, j = 0;

        while (i < this.size() && j < other.size()) {
            T elem1 = this.get(i);
            T elem2 = other.get(j);
            int cmp = elem1.compareTo(elem2);

            if (cmp < 0) {
                result.add(elem1);
                i++;
            } else if (cmp > 0) {
                result.add(elem2);
                j++;
            } else {
                result.add(elem1);
                i++;
                j++;
            }
        }

        while (i < this.size()) {
            result.add(this.get(i++));
        }

        while (j < other.size()) {
            result.add(other.get(j++));
        }

        return new MSet<>(result);
    }

    public MSet<T> intersection(MSet<T> other) {
        List<T> result = new ArrayList<>();
        int i = 0, j = 0;

        while (i < this.size() && j < other.size()) {
            T elem1 = this.get(i);
            T elem2 = other.get(j);
            int cmp = elem1.compareTo(elem2);

            if (cmp < 0) {
                i++;
            } else if (cmp > 0) {
                j++;
            } else {
                result.add(elem1);
                i++;
                j++;
            }
        }

        return new MSet<>(result);
    }

    public MSet<T> symmetricDifference(MSet<T> other) {
        List<T> result = new ArrayList<>();
        int i = 0, j = 0;

        while (i < this.size() && j < other.size()) {
            T elem1 = this.get(i);
            T elem2 = other.get(j);
            int cmp = elem1.compareTo(elem2);

            if (cmp < 0) {
                result.add(elem1);
                i++;
            } else if (cmp > 0) {
                result.add(elem2);
                j++;
            } else {
                i++;
                j++;
            }
        }

        while (i < this.size()) {
            result.add(this.get(i++));
        }

        while (j < other.size()) {
            result.add(other.get(j++));
        }

        return new MSet<>(result);
    }

    public MSet<T> difference(MSet<T> other) {
        List<T> result = new ArrayList<>();
        int i = 0, j = 0;

        while (i < this.size() && j < other.size()) {
            T elem1 = this.get(i);
            T elem2 = other.get(j);
            int cmp = elem1.compareTo(elem2);

            if (cmp < 0) {
                result.add(elem1);
                i++;
            } else if (cmp > 0) {
                j++;
            } else {
                i++;
                j++;
            }
        }

        while (i < this.size()) {
            result.add(this.get(i++));
        }

        return new MSet<>(result);
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj) return true;
        if (obj == null || getClass() != obj.getClass()) return false;
        MSet<?> other = (MSet<?>) obj;
        return elements.equals(other.elements);
    }

    @Override
    public String toString() {
        return "MSet{" + elements + "}";
    }
}